/* 
maze.cpp

Author: Weihang Zhang

Short description of this file: In maze.cpp, the maze input file is read 
and it performs BFS to find the shortest path from start to finish.
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main() {
   int rows, cols, result;
   char** mymaze;
   
   mymaze = read_maze(&rows,&cols); 
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
   result = maze_search(mymaze,rows,cols); 

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
   delete[] mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
   Location start,finish;
   int count1 = 0,count2 = 0;
   for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
         
         if(maze[i][j]=='S'){
            count1++; //counting the number of 'S'
            start.row = i;
            start.col = j;
         }
         
         if(maze[i][j]=='F'){
            count2++; //counting the number of 'S'
            finish.row = i;
            finish.col = j;
         }
      }
   }
   
   if(count1!=1 || count2!=1) return -1; //when bad syntax in input
   
   Queue q(rows*cols);
   q.add_to_back(start);
   Location loc;
   
   //Allocate and initialize the predecessor 2d array
   Location** predecessor = new Location*[rows];
   for(int i=0;i<rows;i++)
      predecessor[i] = new Location[cols];
      
   for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
         predecessor[i][j].row=-1;
         predecessor[i][j].col=-1;
      }
   }
   
   //Allocate and initialize the visited 2d array
   bool** visited = new bool*[rows];
   for(int i=0;i<rows;i++)
      visited[i]= new bool[cols];
   
   for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++)
         visited[i][j] = false;
   }
   
   
   while(q.is_empty()==false){
   
      loc = q.remove_from_front();
      
      //find the cordinates of the four points 
      //surrounding the current location
      Location n,s,e,w;
      n.row = loc.row-1;
      n.col = loc.col;
      
      s.row = loc.row+1;
      s.col = loc.col;
      
      e.row = loc.row;
      e.col = loc.col+1;
      
      w.row = loc.row;
      w.col = loc.col-1;
      
      Location neighbor[4] = {n,s,e,w};
      Location curr;
      
      for(int a=0;a<4;a++){
         //Search around the current location
         curr = neighbor[a];
         if(curr.row>=0 && curr.row<rows && curr.col>=0 && curr.col<cols){
            
            if(maze[curr.row][curr.col]=='.' && visited[curr.row][curr.col]==false){
               //add new step to queue
               visited[curr.row][curr.col]=true;
               predecessor[curr.row][curr.col]=loc;
               q.add_to_back(curr);
            }
            
            else if(maze[curr.row][curr.col]=='F'){
               while(loc.row!=start.row||loc.col!=start.col){
                  //backtracking
                  maze[loc.row][loc.col] = '*';
                  loc = predecessor[loc.row][loc.col];
               }
               
               for(int i=0;i<rows;i++){
                  //deallocating
                  delete[] predecessor[i];
                  delete[] visited[i];
               }
               delete[] predecessor;
               delete[] visited;
               
               return 1;
            }
            
            
         }
      }
      
   }
   // DELETE this stub, it's just for Checkpoint 1 to compile.
   /*for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++)
         cout<<visited[i][j]<<" ";
      cout<<endl;
   }*/
   return 0;
}










