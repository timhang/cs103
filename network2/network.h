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
  vector<int> shortest_path(int from, int to);
  vector<vector<int> > groups();
  vector<int> suggest_friends(int who, int& score);

  bool bfsbool(int from, int end);
  vector<int> bfs(int from, int end);
  
  int depth[100];
  int predecessor[100];
 private:
   vector<User> userlist; //vector of User objects
  
};


#endif
