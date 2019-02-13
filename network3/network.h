/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */
  
#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include "user.h"
#include <fstream>
#include <vector>

class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(User f_user);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  int get_nums();
  User * get_users();
  std::vector<int> shortest_path(int from, int to);
  std::vector<std::vector<int> > groups();
  std::vector<int> suggest_friends(int who, int& score);
  bool bfs(int from, int end);
  std::vector<int> bfs2(int from, int end);



 public:
  int depth[100];
  int predecessor[100];


 private:
 
   User users[100];
   int num;
};


#endif