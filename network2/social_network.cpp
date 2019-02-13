/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */
  
#include "network.h"
#include "user.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    Network networkk;//declare the main network
    if(networkk.read_friends(argv[1])!=0){//error check
        cout<<"Failed to read input file."<<endl;
        return -1;
    }
    bool flag = true;
    int choice;
    while(flag==true){//main loop
        
        //giving the options
        cout<< "Choose the following operations: " << endl;
        cout<<"> 1 Add a user"<<endl;
        cout<<"> 2 Add friend connection"<<endl;
        cout<<"> 3 Remove friend connection"<<endl;
        cout<<"> 4 Print Users"<<endl;
        cout<<"> 5 List friends"<<endl;
        cout<<"> 6 Write to file"<<endl;
        cout<<"> 7 List relations"<<endl;  
        cout<<"> 8 List groups"<<endl;  
        cout<<"> 9 Suggest friends"<<endl;  
        cout<<"Press any other key to exit the program."<<endl;
        
        cin>> choice;
        if(choice==1){//adding an user
            string first,last,full;
            int year,zip;
            cin>>first>>last>>year>>zip;
            full = first+" "+last;
            networkk.add_user(full,year,zip);
            cout<<"Successful"<<endl;
        }

        else if(choice==2){//making a connection
            string first1,last1,full1;
            string first2,last2,full2;
            cin>>first1>>last1;
            full1 = first1+" "+last1;
            cin>>first2>>last2;
            full2 = first2+" "+last2;
            if(networkk.add_connection(full1,full2)==0)
                cout<<"Successful"<<endl;
            else
                cout<<"Error! One or both users do not exist."<<endl;
        }
            
        else if(choice==3){//removing a connection
            string first1,last1,full1;
            string first2,last2,full2;
            cin>>first1>>last1;
            full1 = first1+" "+last1;
            cin>>first2>>last2;
            full2 = first2+" "+last2;
            if(networkk.remove_connection(full1,full2)==0)
                cout<<"Successful"<<endl;
            else
                cout<<"Error! One or both users do not exist."<<endl;
        }
        else if(choice==4){//printing out the entire network of friends
            cout<<left<<setw(5)<<"ID";
            cout<<left<<setw(20)<<"Name";
            cout<<left<<setw(8)<<"Year"<<"Zip"<<endl;
            for(int i=0;i<5+20+8+5;i++)
                cout<<"=";
            cout<<endl;
            for(int i=0;i<networkk.get_list().size();i++){
                User curr = networkk.get_user(i);
                cout<<left<<setw(5)<<curr.get_id();
                cout<<left<<setw(20)<<curr.get_name();
                cout<<left<<setw(8)<<curr.get_year();
                cout<<curr.get_zip()<<endl;
            }
            
        }
        else if(choice==5){//friends of a particular user
            string first,last,full;
            cin>>first>>last;
            full = first+" "+last;
            int id = networkk.get_id(full);
            if(id==-1)
                cout<<"Invalid username."<<endl;
            else{
                cout<<left<<setw(5)<<"ID";
                cout<<left<<setw(20)<<"Name";
                cout<<left<<setw(8)<<"Year"<<"Zip"<<endl;
                for(int i=0;i<5+20+8+5;i++)
                    cout<<"=";
                cout<<endl;
                User chosen = networkk.get_user(id);
                
                for(int i=0;i<chosen.friendlist().size();i++){
                    User buddy = networkk.get_user(chosen.friendlist()[i]);
                    cout<<left<<setw(5)<<buddy.get_id();
                    cout<<left<<setw(20)<<buddy.get_name();
                    cout<<left<<setw(8)<<buddy.get_year();
                    cout<<buddy.get_zip()<<endl;
                }
            }
        }
        else if(choice==6){//write the network onto a file
            cout<<"Enter file name: ";
            string filename;
            cin>>filename;
            networkk.write_friends(filename.c_str());
            cout<<"Write successfully."<<endl;
        }
        else if(choice==7){//Finding the min distance between 2 users
            string first1,last1,full1;
            string first2,last2,full2;
            cin>>first1>>last1;
            full1 = first1+" "+last1;
            cin>>first2>>last2;
            full2 = first2+" "+last2;
            int id1 = networkk.get_id(full1);
            int id2 = networkk.get_id(full2);
            vector<int> ans = networkk.shortest_path(id1,id2);
            if (ans.size()==0)
                cout<< "None"<<endl;
            else{
                cout<<"Distance: "<<ans.size()-1<<endl;
                User temp = networkk.get_list()[ans[0]];
                cout<< temp.get_name()<<" ";
                for(int i=1;i<ans.size();i++){
                    temp = networkk.get_list()[ans[i]];
                    cout<<"-> "<<temp.get_name();
                }
                cout<<endl<<endl;
            }
        }
        else if(choice==8){//Print the groups
            vector<vector<int> > groups = networkk.groups();
            for(int i=0;i<groups.size();i++){
                cout<<"Set "<<i+1<<" => ";
                cout<<networkk.get_list()[groups[i][0]].get_name();
                
                for(int j=1;i<groups[i].size();j++)
                    cout<<", "<<networkk.get_list()[groups[i][j]].get_name();
                cout<<endl<<endl;
            }
            
        }
        else if(choice==9){//Make a friend suggestion
            int score;
            string first,last,full;
            cin>>first>>last;
            full = first+" "+last;
            int id = networkk.get_id(full);
            vector<int> ans = networkk.suggest_friends(id,score);
            if(ans.size()==0)
                cout<<"None"<<endl<<endl;
            else{
                cout<<"The suggested friend(s) is/are:"<<endl;
                for(int i=0;i<ans.size();i++){
                    cout<<"  "<<left<<setw(20)<<networkk.get_list()[ans[i]].get_name()
                    <<"Score: "<<score<<endl;
                }
                cout<<endl;
            }
        
        
        }
        else break;//exit loop
    }
    return 0;
}










