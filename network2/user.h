/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */

#ifndef USER_H
#define USER_H
#include <cstring>
#include <vector>
#include <string>
using namespace std;

class User {
 public:
    User(int i,std::string n,int y,int z);

    void add_friend(int i);
    void remove_friend(int j);
    std::string get_name();
    int get_id();
    int get_year();
    int get_zip();
    vector<int> friendlist();

    //int depth();
    //int predecessor();
 private:
    int id;
    std::string name;
    int year;
    int zip;
    vector<int> connections;//vector of friend's ids
};


#endif
