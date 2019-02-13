/*Author: Weihang Zhang
  Email:  weihangz@usc.edu */

#include <string>
#include "user.h"

using namespace std;

User::User(int u_id, string u_name, int u_year, int u_zip)
{
 id = u_id;
 name = u_name;
 year = u_year;
 zip = u_zip;
 num_friends = 0;
 }
 
User::User()
{
}
 User::~User() {}
 
 void User::add_friend (int friend_id) //
 {
    int n = get_num();
    for (int i=0; i<n; i++)
    {
      if (friends[i] == friend_id)
      return;
    }
      
    
    friends[n] = friend_id;
    num_friends++;
 }
 void User::delete_friend (int friend_id) //
 {
     int n = get_num();
     for (int i=0; i<n; i++)
     {
       if (friends[i] == friend_id)
       {
         for (int j=i; j<(n-1); j++)
         {
            friends [j] = friends [j+1];
         
         }
        }
       }
       num_friends--;
      
 }
 
 
      int User::get_id()
      {
         return id;
      }
      string User::get_name()
      {
         return name;
      }
      
      int User::get_year()
      {
         return year;
      }
      int User::get_zip()
      {
         return zip;
      }
      
      int* User::get_friends() 
      {
         return friends;
      }
      int User::get_num()
      {
         return num_friends;
      }
