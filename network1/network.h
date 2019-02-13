/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */
  
#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include "user.h"
#include <vector>
using namespace std;

class Network {
 public:
  //Network();

  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  User get_user(int id);
  vector<User> get_list();
 private:
   vector<User> userlist; //vector of User objects
  
};


#endif
