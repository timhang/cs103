/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */

#include <vector>
#include "network.h"
#include "user.h"
#include <string>
#include <fstream>
#include <sstream>
#include <deque>

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

//Part 2
vector<int> Network::shortest_path(int from, int to){
    for(int i=0;i<100;i++){
        depth[i] = -1;
        predecessor[i] = -1;
    }
    vector<int> ans;
    if(from==to){
        ans.push_back(from);
        return ans;
    }
    if(bfsbool(from,to)){
        ans.push_back(to);
        int n=predecessor[to];
        while(n!=from){
            ans.push_back(n);
            n = predecessor[n];
        }
        ans.push_back(from);
        for(int i=0;i<ans.size()/2;i++){
            int ans1 = ans[i];
            ans[i] = ans[ans.size()-1-i];
            ans[ans.size()-1-i] = ans1;
        }
    }
    return ans;

}

vector<vector<int> > Network::groups(){
    vector<vector<int> > ans;
    for(int i=0;i<100;i++){
        depth[i] = -1;
        predecessor[i] = -1;
    }
    
    for(int i=0;i<userlist.size();i++){
        if(predecessor[i]==-1)
            ans.push_back(bfs(i,-1));
    }
    
    return ans;
}

vector<int> Network::suggest_friends(int who, int& score){
    bool suggestions[100];
    for(int i=0;i<100;i++) 
        suggestions[i] = 1;
        
    suggestions[who] = 0;
    for(int i=0;i<userlist[who].friendlist().size();i++)
        suggestions[userlist[who].friendlist()[i]] = 0;
    
    vector<int> ans;
    int max = 0;
    for(int i=0;i<userlist.size();i++){
        if(suggestions[i]==true){
            int fs = 0;
            for(int j=0;j<userlist[i].friendlist().size();j++){
                for(int k=0;k<userlist[who].friendlist().size();k++){
                    if(userlist[i].friendlist()[j]==userlist[who].friendlist()[k])
                        fs++;
                    
                }
            }
            if(fs>max){
                max = fs;
                while(ans.size()>0)
                   ans.pop_back();
                ans.push_back(i);
            }
            else if(fs==max)
                ans.push_back(i);
            
        }
    }
    score = max;
    return ans;
}


bool Network::bfsbool(int from,int end){
    deque<int> span;
    span.push_back(from);
    while(span.size()!=0){
        int temp = span.front();
        span.pop_front();
        if(temp == end)
            return true;
        for(int i=0;i<userlist[temp].friendlist().size();i++){
            int  temp1 = userlist[userlist[temp].friendlist()[i]].get_id();
            depth[temp1] = depth[temp] +1;
            predecessor[temp1] = temp;
            span.push_back(temp1);
        }
    }    
    return false;
}

vector<int> Network::bfs(int from,int end){
    vector<int> ans;
    deque<int> span;
    span.push_back(from);
    ans.push_back(from);
    depth[from] = 0;
    while(span.size()!=0)
    {
        int temp = span.front();
        span.pop_front();
        if(temp == end)
            return ans;

        for(int i=0;i<userlist[temp].friendlist().size();i++){
            int temp1 = userlist[userlist[temp].friendlist()[i]].get_id();
            if(depth[temp1]==-1){
                depth[temp1] = depth[temp] +1;
                predecessor[temp1] = temp;
                span.push_back(temp1);
                ans.push_back(temp1);
            }
        }
    }   
    return ans;
}











