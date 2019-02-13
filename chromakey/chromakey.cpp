/*********************************************************************
 File:     chromakey.cpp

 Author:   Weihang Zhang

 Email address: weihangz@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  // Image data array
  // Note:  DON'T use the static keyword except where we expressly say so.
  //        It puts the large array in a separate, fixed, area of memory. 
  //        It is bad practice. But useful until we have dynamic allocation.
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold " 
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }
	
  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
  threshold = atof (argv[3]);

  // Call Method 1 Function
  method1(inputImage,chromaMask,threshold);

  // Produce the output by calling replace()
  replace(chromaMask,inputImage,bgrndImage,outputImage);
  
  /*for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
          cout<<chromaMask[i][j]<<" ";
      }
      cout<<endl;
  }*/
  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
  method2(inputImage,chromaMask);

  // Produce the output by calling replace()
  replace(chromaMask,inputImage,bgrndImage,outputImage);

  // Write the output image to a file using the filename argv[5]
  
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold)
{
  //determining the average value of the RGB vector of green screen
  double distance;
  double tot1[3]={0,0,0},avg1[3];
  for (int i=0;i<40;i++){
      for(int j=0;j<40;j++){
          for(int k=0;k<3;k++)
              tot1[k] = tot1[k] + inImage[i][j][k];
      }
  }
  
  for(int i=0;i<3;i++)
     avg1[i] = tot1[i]/1600; //dividing total by 40*40 to get average value
  
  
  for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
           //calculating distance
           double a = pow(inImage[i][j][0]-avg1[0],2.0);
           double b = pow(inImage[i][j][1]-avg1[1],2.0);
           double c = pow(inImage[i][j][2]-avg1[2],2.0);
           distance = sqrt(a+b+c); //distance from the average value of background
           
           //cout<<distance<<" "; this was to check if calculations are good
           
           if (distance>threshold) //making the mask
               mask[i][j]=true;
           else
               mask[i][j]=false;

      }
      //cout<<endl;
  }
  

}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{
  double distance[SIZE][SIZE];
  double tot1[3]={0,0,0},avg1[3];
  double tot2[3]={0,0,0},avg2[3];
  for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
          for(int k=0;k<3;k++){
             //totaling the RGB value of every pixel
             tot2[k]=tot2[k] + inImage[i][j][k];
             
             if(i<40 && j<40) //the top-left 40x40 square as background sample
                 tot1[k] = tot1[k] + inImage[i][j][k];
          }
      }
  }
  

  double threshold,a,b,c;
  
  for(int i=0;i<3;i++){ //calculate the average
     avg1[i] = tot1[i]/1600; //average RGB value of top-left sample square
     avg2[i] = tot2[i]/double(SIZE*SIZE); //average RGB value of all pixels
  }
  
  //finding the distance between average of sample and average of all pixels
  a = pow(avg2[0]-avg1[0],2.0);
  b = pow(avg2[1]-avg1[1],2.0);
  c = pow(avg2[2]-avg1[2],2.0);
  double allavg = sqrt(a+b+c);
  

  double tot=0;
  for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
           //calculating the distance between each pixel and the average of sample
           a = pow(inImage[i][j][0]-avg1[0],2.0);
           b = pow(inImage[i][j][1]-avg1[1],2.0);
           c = pow(inImage[i][j][2]-avg1[2],2.0);
           distance[i][j] = sqrt(a+b+c); //storing them in a 2D array
           tot = tot+distance[i][j]; //totaling the distance for standard deviation
       }
  }
  double avg3 = tot/double(SIZE*SIZE);
  
  //finding the standard deviation of distance to sample RGB
  double stdv;
  for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
          double temp = pow(distance[i][j]-avg3,2.0);
          stdv = stdv + temp; //Sigma[(x-x_avg)^2]
      }
  }
  stdv = stdv/double(SIZE*SIZE-1); // numerator/(N-1)
  stdv = sqrt(stdv); //square root the whole fraction to get st. deviation

  threshold = sqrt(stdv/allavg-1) * stdv; //Formula to derive the threshold
  //The formula is derived through intuition and trial and error
  
  for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
           //filling in the mask array based on threshold value
           //cout<<distance<<" ";
           if (distance[i][j]>threshold)
               mask[i][j]=true;
           else
               mask[i][j]=false;

      }
      //cout<<endl;
  }

  

}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image
  for (int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
      
          if(mask[i][j]==false){
              for(int k=0;k<3;k++)
                  outImage[i][j][k]=bgImage[i][j][k];
          }
          
          else{
              for(int k=0;k<3;k++)
                  outImage[i][j][k]=inImage[i][j][k];
          }
          
      }
  }


}
