/********************************************************
 * CS 103 Zombie-pocalypse PA
 * Name: Weihang Zhang
 * USC email: weihangz@usc.edu
 * Comments (you want us to know):
 * In this program, I will use a combination of while loops, for loops,
 * if statements and random operations to simulate a zombie apocalypse.
 ********************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
  // Array with enough entries for the maximum population size possible.
    bool pop[MAXPOP];

  // Your code here
    int N,k,M,s;
    cout<<"Enter the following: N k M seed"<<endl;
    cin>>N>>k>>M>>s;
    srand(s);
    
   
    int index,counter,nights,sum,min,max,nzombies;
    sum=0; min=0; max=0;
    for(int a=0;a<M;a++){
        
        // Initializing the conditions before every simulation
        nights = 0;
        nzombies=k;
        for(int i=0;i<N;i++){
            if(i<k)
               pop[i]=true;
            else
               pop[i]=false;
 
        }
        
        // Counter counts the number of zombies converted each night
        while(nzombies<N){
            nights++;
            counter = 0;
            for(int i=0;i<nzombies;i++){
                
                // Generating ramdom number
                index = rand() % N;
                
                // Biting
                if(pop[index]==false){
                    pop[index]=true;
                    counter++;
                }
            }
            
            // Number of zombies in total
            nzombies=nzombies+counter;
        }
        
        sum = sum + nights;
        
        // Conditionals used to obtain maximum and minimum nights needed
        if(a==0){
            min=nights;
            max=nights;
        }
        else{
            if(nights<min)
                min=nights;
            if(nights>max)
                max=nights;
        }

    }
  
  // Print out your average, max, and min number of nights here
  // Be sure to follow the format shown in the assignment writeup.
    double avg = double(sum)/double(M);
    
    cout<<"Average Nights: "<<avg<<endl;
    cout<<"Max Nights: "<<max<<endl;
    cout<<"Min Nights: "<<min<<endl;
    return 0;
}
