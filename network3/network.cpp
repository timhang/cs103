/*Author: Weihang Zhang
  email: weihangz@usc.edu
  */
#include "network.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <deque>



using namespace std;

Network::Network()
{
   User tmp;
   for (int i = 0; i < 100; i++)
   {
   users[i] = tmp;
   }
}

Network::~Network()
{
}

int Network::get_nums()  //get the num of users
{
   return num;
}

void Network::add_user(User f_user)
{
   
   users[num] = f_user;
   num++;
  

}
int Network::read_friends(const char* fname)
{
   ifstream inFile(fname);
   if(inFile.fail())
   {
      return -1;
   }
   
  // int num;
   inFile >> num;
   

   for (int i=0; i<num; i++)
   {
      int t_id, t_year, t_zip;
      string t_first, t_last;
      string t_name;
      
      
      inFile>>t_id;
      inFile>>t_first>>t_last;
      t_name = t_first + " " + t_last; 
      inFile>>t_year;
      inFile>>t_zip;
      
      string myline;
      getline(inFile, myline); //new line 
      getline(inFile, myline);
      stringstream ss(myline);
      User t_user(t_id, t_name, t_year, t_zip);
      users[i] = t_user;
      
      int nums;
      
      ss>>nums;
      
      while(!ss.fail())
      {
         users[i].add_friend(nums);
         //cout << nums << "/";
         ss>>nums;
        }
   }
     return 0;
      
         
}

int Network::write_friends(const char *fname)
{
   ofstream oFile (fname);
  
   oFile<<num<<endl;
   
   for (int i=0; i<num; i++)
   {
      
      
      User a_user = users[i];
      oFile<<a_user.get_id()<<endl;
       
      oFile<<'\t'<<a_user.get_name()<<endl; //name
      oFile<<'\t'<<a_user.get_year()<<endl; //year
      oFile<<'\t'<<a_user.get_zip()<<endl;  //zip
      
      oFile<<'\t';
      //cout << a_user.get_num() << "=";
      if(a_user.get_num()>0)
      {  
         oFile<<a_user.get_friends()[0];
         for(int j=1; j<a_user.get_num();j++)
         {
            //cout << a_user.get_friends()[j] << "/";
            oFile<<" " <<a_user.get_friends()[j];
           
      
         }
        }
      
      oFile<<endl; //
      
   
   
   }
   if (oFile.fail())
   {
      return -1;
   }
   
   return 0;

}


int Network:: get_id(string username)
{
   for(int i=0; i<get_nums(); i++)  
   {
      if(users[i].get_name() == username)
         return i;  //users[i].get_id()
    }
    return -1;
  
 }
 
int Network::add_connection(string name1, string name2)
{
   int id1 = -1;
   int id2 = -1;
   //int temp;

   for(int i=0; i<get_nums();i++)
   {
      if(users[i].get_name() == name1)
      {  
         //temp = i;
         id1 = get_id(name1);
      }
      else if(users[i].get_name() == name2)
      {
         id2 = get_id(name2);
      }
    }
    
    //if either user is invalid
    if (id1==id2 || id1==-1 || id2==-1)
    {
      return -1;
    }
    
    
    else
    {
    users[id1].add_friend(id2);
    users[id2].add_friend(id1);
    return 0;
    }
     

}

int Network::remove_connection(string name1, string name2)
{
   int id1 = -1;
   int id2 = -1;
   //int temp;
   for(int i=0; i<get_nums();i++)
   {
      if(users[i].get_name() == name1)
      {  
         id1 = i;
         //temp = i;
         //id1 = get_id(name1);
      }
      else if(users[i].get_name() == name2)
      {
         id2 = i;
      }
    }
    if (id1==id2 || id1==-1 || id2==-1)
    {
      return -1;
    }
    
   else
   {
    users[id1].delete_friend(id2);
    users[id2].delete_friend(id1);
    return 0;
   }
    

}

 User* Network::get_users()
 {
   return users;
 }

std::vector<int> Network::shortest_path(int from, int to)
{
    for (int i = 0; i < 100; i++)
    {
        depth[i] = -1;
        predecessor[i] = -1;
    }
    std::vector<int> result;
    if (from == to)
    {
        result.push_back(from);
        return result;
    }
    if (bfs(from, to))
    {
        result.push_back(to);
        int pre = predecessor[to];
        while (pre != from)
        {
            result.push_back(pre);
            pre = predecessor[pre];
        }
        result.push_back(from);
        for (int i = 0; i < result.size()/2; i++)
        {
            int resulttmp = result[i];
            result[i] = result[result.size() -1-i];
            result[result.size() -1-i] = resulttmp;
        }
    }
    return result;

}

bool Network::bfs(int from, int end)
{
    deque<int> path;
    path.push_back(from);
    while (path.size() != 0 )
    {
        int tmp = path.front();
        path.pop_front();
        if (tmp == end)
        {
            return true;
        }
        int numoff = users[tmp].get_num();
        for (int i = 0; i < numoff; i++)
        {
            int  ftmp = users[users[tmp].get_friends()[i]].get_id();
            depth[ftmp] = depth[tmp] +1;
            predecessor[ftmp] = tmp;
            path.push_back(ftmp);
        }
    }    
    return false;
}
std::vector<int> Network::bfs2(int from, int end)
{
    std::vector<int> result;
    deque<int> path;
    path.push_back(from);
    result.push_back(from);
    depth[from] = 0;
    while (path.size()  != 0 )
    {
        int tmp = path.front();
        path.pop_front();
        if (tmp == end)
        {
            return result;
        }
        int numoff = users[tmp].get_num();
        for (int i = 0; i < numoff; i++)
        {
            int  ftmp = users[users[tmp].get_friends()[i]].get_id();
            if (depth[ftmp] == -1){
            depth[ftmp] = depth[tmp] +1;
            predecessor[ftmp] = tmp;
            path.push_back(ftmp);
            result.push_back(ftmp);
        }
        }
    }   
    return result;
}

std::vector<std::vector<int> > Network::groups()
{
    std::vector<std::vector<int> > groupresult;
    //cout <<"p1";
    for (int i = 0; i < 100; i++)
    {
        depth[i] = -1;
        predecessor[i] = -1;
        //cout << "p2";
    }
    
    for (int i = 0; i < num; i++)
    {
        if (predecessor[i] == -1)
        {
            groupresult.push_back(bfs2(i, -1));
        }
    }
    //groupresult.push_back(bfs2(0, 3));
    return groupresult;
}
std::vector<int> Network::suggest_friends(int who, int& score)
{
    int potential[100];
    for (int i = 0; i < 100; i++) 
    {
        potential[i] = 1;
    }
    potential[who] = 0;
    for (int i = 0; i < users[who].get_num(); i++)
    {
        potential[users[who].get_friends()[i]] = 0;
    }
    std::vector<int> result;
    int max = 0;
    for (int i = 0; i< num;i++)
    {
        if (potential[i])
        {
            int fscore = 0;
            for (int j = 0; j < users[i].get_num(); j++)
            {
                for (int k = 0; k < users[who].get_num(); k++)
                {
                    if (users[i].get_friends()[j]
                        == users[who].get_friends()[k])
                    {
                        fscore ++;
                    }
                }
            }
            if (fscore > max)
            {
                max = fscore;
                while(result.size()>0) {result.pop_back();}
                result.push_back(i);
            }
            else if (fscore == max)
            {
                result.push_back(i);
            }
        }
    }
    score = max;
    return result;
}