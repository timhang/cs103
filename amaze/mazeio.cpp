/* 
mazeio.cpp

Author:

Short description of this file:
read the file into the main program and print the resulting maze out.
*/

#include <iostream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from cin into a dynamically allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * such as integers for the size not found.
 *
 * We also pass in two pointers to integers. Fill 
 * the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(int* rows, int* cols) {
   // FILL THIS IN
   cin>>*rows;
   cin>>*cols;
   int row = *rows; int col = *cols;
   char** newmaze = new char*[row];
   for(int i=0;i<row;i++){
      newmaze[i]=new char[col];
   }
   
   for(int i=0;i<row;i++){
      for(int j=0;j<col;j++)
         cin>>newmaze[i][j];
   }
   
   return newmaze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) {
   // FILL THIS IN
   cout<<rows<<" "<<cols<<endl;
   for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++)
         cout<<maze[i][j];
      cout<<endl;
   }
}

