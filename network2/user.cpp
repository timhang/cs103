/*Author: Weihang Zhang
  Email:  weihangz@usc.edu */

#include "user.h"
#include "network.h"
#include <vector>
#include <string>


User::User(int i, std::string n,int y,int z){//Constructor
	id = i;
	name = n;
	year = y;
	zip = z;
}


void User::add_friend(int i){//make a friend
	bool flag=false;
	for(int j=0;j<connections.size();j++){
		if(i==connections[j]) flag = true;
	}
	if(flag == false)
		connections.push_back(i);
	//userlist[i].connections.push_back(id);
}

void User::remove_friend(int j){//delete a friend
	for(int i=0;i<connections.size();i++){
		if(connections[i]==j)
			connections.erase(connections.begin()+i);
	}
	/*for(int i=0;i<a.connections.size();i++){
		if(a.connections[i]==id)
			a.connections.erase(a.connections.begin()+i);
	}*/
}

std::string User::get_name(){
	return name;}

int User::get_id(){
	return id;}

int User::get_year(){
	return year;}

int User::get_zip(){
	return zip;}

vector<int> User::friendlist(){//return the vector of connections
	return connections;
	}




