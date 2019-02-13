/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */

#include <vector>
#include "network.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


/*Network::Network(){

}*/


int Network::read_friends(const char *filename){
    //reading the input file
    ifstream input(filename);
    if(input.fail()) return -1;
 	int count;
 	input>>count;
 	for(int i=0;i<count;i++){
 	    int id;
 	    input>>id;
 	    string first,last,full;
 	    input>>first>>last;
 	    full=first+" "+last;
 	    int year;
 	    input>>year;
 	    int zip;
 	    input>>zip;
 	    User a(id,full,year,zip);
 	    userlist.push_back(a);
 	    string friends;
 	    getline(input,friends);
 	    getline(input,friends);
 	    
 	    //reading friends into a vector<int>
 	    std::istringstream ss;
 	    ss.str(friends);
 	    int friend_id;
 	    ss>>friend_id;
 	    while(!ss.fail()){ //check for failures
 	        userlist[i].add_friend(friend_id);
 	        ss>>friend_id;
 	    }
 	}
 	
 	if(input.fail()) return -1;
 	return 0;
}

int Network::write_friends(const char *filename){

    //write network onto an output file
	ofstream output(filename);
	output<<userlist.size()<<endl;
    for(int i=0;i<userlist.size();i++){
        output<<userlist[i].get_id()<<endl;
        output<<'\t'<<userlist[i].get_name()<<endl;
        output<<'\t'<<userlist[i].get_year()<<endl;
        output<<'\t'<<userlist[i].get_zip()<<endl;
        output<<'\t';
        if(userlist[i].friendlist().size()>0){
            for(int j=0;j<userlist[i].friendlist().size();j++)
                output<<userlist[i].friendlist()[j]<<" ";
        }
        output<<endl;
    }
    if(output.fail()) return -1;
    return 0;
}

void Network::add_user(std::string username, int yr, int zipcode){
    //add an user to the network 
    User newuser(userlist.size(),username,yr,zipcode);
    userlist.push_back(newuser);
}

int Network::add_connection(std::string name1, std::string name2){
    //add connection between two friends
    int id1=get_id(name1);
    int id2=get_id(name2);
    if(id1==-1||id2==-1) return -1; //error check
    
    userlist[id1].add_friend(id2);
    userlist[id2].add_friend(id1);
    return 0;
}
int Network::remove_connection(std::string name1, std::string name2){
    //remove connections between two ex-friends
    int id1=get_id(name1);
    int id2=get_id(name2);
    if(id1==-1||id2==-1) return -1; // error check;
    
    userlist[id1].remove_friend(id2);
    userlist[id2].remove_friend(id1);
    return 0;
}

int Network::get_id(std::string username){
    //get user's id given user's name
    for(int i=0;i<userlist.size();i++){
       if(username==userlist[i].get_name()) return userlist[i].get_id();
    }
    return -1;
}

User Network::get_user(int id){
    //return an User object
    return userlist[id];
}

vector<User> Network::get_list(){
    //return the User vector
    return userlist;
}












