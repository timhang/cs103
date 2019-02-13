/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */
  
#include "network.h"
#include "user.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//print our menu
void menu() 
{
   cout << "Option 1: Add a user" << endl;
   cout << "Option 2: Add connection"<<endl;
   cout << "Option 3: Remove friend connection"<<endl;
   cout << "Option 4: Print users"<<endl; 
   cout << "Option 5: List friends"<<endl; 
   cout << "Option 6: Write file"<<endl;  
   cout << "Option 7: List relation"<<endl;  
   cout << "Option 8: List groups"<<endl;  
   cout << "Option 9: Suggest firend"<<endl;  
}

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
   
      return -1;
   }
   

   Network soNet;
   
   if(soNet.read_friends(argv[1])==-1)
   {
      return -1;
   
   }
   /*
   std::vector<int> testresult = soNet.shortest_path(0,0);
   for (int i = 0; i < testresult.size(); i++)
   {
        cout << testresult[i] << "/";
   }
   cout << endl;
   std::vector<std::vector<int> > groups = soNet.groups();
   //cout <<"Comp" <<endl;
   for (int i = 0; i <groups.size(); i++)
   {
        for (int j = 0; j < groups[i].size(); j++)
        {
            cout << groups[i][j] << "/";
        }
        cout << endl;
   }
   cout << endl;
   */
   int option;
//loop, users enter option
while(1)
{  
  menu();
   cin >> option;
   if(option==1)
   {
      string first, last, name;
      int year, zip;
      cin>>first>>last>>year>>zip;
      name = first + " " + last;
      int id = soNet.get_nums();
      User my_user(id, name, year, zip);
      soNet.add_user(my_user);
      
   
   }
   
   else if(option ==2)
   {
      string first1, last1, first2,last2, name1, name2;
      cin>>first1>>last1>>first2>>last2;
      name1 = first1 + " " + last1;
      name2 = first2 + " " + last2;
      
      int i = soNet.add_connection(name1, name2);
      if(i==-1)
      {
      cout<<"error: a user does not exist"<<endl;
      
      }
      
   
   }
   else if(option==3)
   {
      string first1, last1, first2,last2, name1, name2;
      cin>>first1>>last1>>first2>>last2;
      name1 = first1 + " " + last1;
      name2 = first2 + " " + last2;
   
      int i= soNet.remove_connection(name1, name2);
      if(i==-1)
      {
         cout<<"error: user does not exist or users are not friend"<<endl;
      }
      
   }
   else if(option == 4)
   {
      cout << left;
      
      cout << setw(10) << "ID" << setw(30) << "Name" << setw(10) 
      << "Year"<< setw(10) << "Zip" << endl;
      
      
      cout<< setfill('=') << setw(60) << "" << setfill(' ') << endl;
      
      User* u = soNet.get_users();
      for(int i = 0; i < soNet.get_nums(); i++)
        {
         cout<<setw(10)<<i<<setw(30)<<(u+i)->get_name()<<setw(10)
         <<(u+i)->get_year()<<setw(10)<<(u+i)->get_zip()<<endl;
        }
        
   }
   
   else if(option == 5)
   {
      string first, last, name;
      cin>>first>>last;
      name = first + " " + last;
      
      int id = soNet.get_id(name);
      
      if(id==-1)
      {
        cout<<"error: user does not exist"<<endl;
       }
       else
       {
         User* u = soNet.get_users();
         User my_user = *(u+id);
         
        
         int* f = my_user.get_friends();
         
         
         
         cout<<left;
         cout << setw(10) << "ID" << setw(30) << "Name" << setw(10) 
         << "Year"<< setw(10) << "Zip" << endl;
         cout<< setfill('=') << setw(60) << "" << setfill(' ') << endl;
         
         for(int i=0; i<my_user.get_num();i++)
         {
            User fri = *(u+*(f+i));
           
             int f_id = fri.get_id();
             string f_name = fri.get_name();
             int f_year = fri.get_year();
             int f_zip = fri.get_zip();
            
          cout<<setw(10)<<f_id<<setw(30)<<f_name<<setw(10)
         <<f_year<<setw(10)<<f_zip<<endl;
           
           //print friends 
          }
          
    }
      
    }
    else if(option ==6)
    {
      string file;
      cin>>file;
      const char* c = file.c_str();
      //soNet.write_friends(const char *fname);
      soNet.write_friends(c);
       
     }
    else if(option == 7)
    {
        string first1, last1, first2,last2, name1, name2;
        cin>>first1>>last1>>first2>>last2;
        name1 = first1 + " " + last1;
        name2 = first2 + " " + last2;
        int id1 = soNet.get_id(name1);
        int id2 = soNet.get_id(name2);
        std::vector<int> result = soNet.shortest_path(id1,id2);
        int size = result.size();
        if (size == 0)
        {
            cout << "None" << endl;
        }
        else
        {
            cout <<"Distance: "<< size-1 << endl;
            User u = soNet.get_users()[result[0]];
            cout << u.get_name() << " ";
            for (int i = 1; i < size; i++)
            {
                u = soNet.get_users()[result[i]];
                cout << "-> " <<u.get_name();
            }
        }
    }
    else if(option == 8)
    {
        std::vector<std::vector<int> > groups = soNet.groups();
        int size = groups.size();
        for (int i = 0; i < size; i++)
        {
            cout << "Set " << i+1 << " => ";
            cout << soNet.get_users()[groups[i][0]].get_name();

            for (int j = 1; j < groups[i].size(); j++)
            {
            cout << ", "<< soNet.get_users()[groups[i][j]].get_name();
            }
            cout << endl;
        }
    }
    else if(option == 9)
    {
        int score;
        string first, last, name;
        cin>>first>>last;
        name = first + " " + last;
        int id = soNet.get_id(name);
        std::vector<int> result = soNet.suggest_friends(id, score);
        if (result.size() == 0)
        {
            cout << "None" << endl;

        }
        else{
        cout << "THe suggested friend(s) is/are:" << endl;
        for (int i = 0; i < result.size(); i++)
        {
            cout << "   " << left << setw(20) << soNet.get_users()[result[i]].
            get_name() << "Score: "<< score << endl;
        }
    }

    }
     else
     {
      break;
     }
 }
}








