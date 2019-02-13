/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */

#ifndef USER_H
#define USER_H
#include <string>


class User {
 public:
      User(int id, std::string name, int year, int zip); 
      User();
      //destructor
      ~User();
      
      void add_friend(int friend_id);
      void delete_friend(int friend_id);
      
      //accessors
      int get_id();
      std::string get_name();
      int get_year();
      int get_zip();
      int get_num();
      int* get_friends();
     
     
      //mutators
     
      
     
 private:
   int id;
   std::string name;
   int year;
   int zip;
   
   int friends[100];
   
   int num_friends;
   

};


#endif
