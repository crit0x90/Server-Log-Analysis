#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <chrono>
#include <unistd.h>
#include <utility>
#include <set>
#include "header.h"
using chrono::system_clock;
using namespace std;

//GLOBAL VARIABLES
int freelist_size = 0;

int floodThreshold = 10;
int userThreshold = 3;
int ipThreshold = 3;

int flood_lookahead = 0;
int user_lookahead = 0;
int ip_lookahead = 0;

void start()
{
    string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:38 -0700]";

    Freelist* freelist = new Freelist(freelist_size); //freelist
    priority_queue<pair<time_t, Userdata*> > pQueue;  //priority queue
    map<string, int> floodMap; //flood map
    map<string, map<string, int> > ipMap; //ip map, ip -> map<usr, num_occurances>
    map<string, map<string, int> > userMap; //user map, username -> map<ip, num occurances>
    string lineInput;
    system_clock::time_point currentTime = system_clock::now();
    time_t tt;

    currentTime = system_clock::now(); //get current time
    tt = system_clock::to_time_t(currentTime);//format

//set record info
    Userdata* record = freelist->getNode(testLine); //no timestamps yet
    record->floodStamp = tt + flood_lookahead;
    record->userStamp  = tt + user_lookahead;
    record->ipStamp = tt + ip_lookahead;

//put in queue
    pQueue.push(make_pair(record->floodStamp, record));
    pQueue.push(make_pair(record->userStamp, record));
    pQueue.push(make_pair(record->ipStamp, record));

//update data structures

    //update flood map
    if(floodMap.count(record->IPaddress))
    {
        //the key is already in the map
        floodMap[record->IPaddress]++;
    }
    else
    {
        //not in map so insert
        floodMap.insert(pair<string, int>(record->IPaddress, 1));
    }

    //check to see if the outer if else is necessary later
    //update ip map
    if(ipMap.count(record->IPaddress))
    {
        //the username is already in the map
        if(ipMap[record->IPaddress].count(record->IPaddress))
        {
            //the ip is already in the map
            ipMap[record->IPaddress][record->username]++;
        }
        else
        {
            //the ip is not in the map
            ipMap[record->IPaddress][record->username] = 1;
        }
    }
    else
    {
        //username isnt in the map
        ipMap[record->IPaddress][record->username] = 1;
    }

    //update user map
    if(userMap.count(record->username))
    {
        //the username is already in the map
        if(userMap[record->username].count(record->IPaddress))
        {
            //the ip is already in the map
            userMap[record->username][record->IPaddress]++;
        }
        else
        {
            //the ip is not in the map
            userMap[record->username][record->IPaddress] = 1;
        }
    }
    else
    {
        //username isnt in the map
        userMap[record->username][record->IPaddress] = 1;
    }

//check if alert is triggered
    if(floodMap[record->IPaddress] > floodThreshold)
    {
        //alertAdministrator();
    }

    if(ipMap[record->IPaddress][record->username] > ipThreshold)
    {
        //alertAdministrator();
    }

    if(userMap[record->username][record->IPaddress] > userThreshold)
    {
        //alertAdministrator();
    }

//expire data
    Userdata* comp_node = pQueue.top().second;
    //while(tt > pQueue.top().first)
    //{
        comp_node = pQueue.top().second;
        
        //flood expire
        if(tt == comp_node->floodStamp)
        {
            floodMap[record->IPaddress]--;
            comp_node->floodStamp = -1;

            //if no unexpired data left return to free list
            if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
            {
                freeNode(comp_node); //resets node data
                //put back on free list
                comp_node->free_next = freelist->freelist_head;
                freelist->freelist_head->free_next = comp_node;
            }
        }

        //ip expire
        if(tt == comp_node->ipStamp)
        {
            userMap[comp_node->IPaddress][comp_node->username]--;
            comp_node->ipStamp = -1;

            //if there are no more instances of the ip then remove that listing
            if(userMap[comp_node->IPaddress][comp_node->username] == 0)
            {
                userMap[comp_node->IPaddress].erase(comp_node->username);
                //if there are no more ips at all then remove this user
                if(userMap[comp_node->IPaddress].size() == 0)
                {
                    userMap.erase(comp_node->IPaddress);
                }
            }

            //if no unexpired data left return to free list
            if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
            {
                freeNode(comp_node); //resets node data
                //put back on free list
                comp_node->free_next = freelist->freelist_head;
                freelist->freelist_head->free_next = comp_node;
            }
        }

        //user expire
        if(tt == comp_node->userStamp)
        {
            userMap[comp_node->username][comp_node->IPaddress]--;
            comp_node->userStamp = -1;

            //if there are no more instances of the ip then remove that listing
            if(userMap[comp_node->username][comp_node->IPaddress] == 0)
            {
                userMap[comp_node->username].erase(comp_node->IPaddress);
                //if there are no more ips at all then remove this user
                if(userMap[comp_node->username].size() == 0)
                {
                    userMap.erase(comp_node->username);
                }
            }

            //if no unexpired data left return to free list
            if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
            {
                freeNode(comp_node); //resets node data
                //put back on free list
                comp_node->free_next = freelist->freelist_head;
                freelist->freelist_head->free_next = comp_node;
            }
        }


    //}

    /*
    while (getline(cin,lineInput)) 
    {
        currentTime = system_clock::now(); //get current time
        tt = system_clock::to_time_t(currentTime);//format

        //set record info
        Userdata* record = freelist->getNode(lineInput); //no timestamps yet
        record->floodStamp = tt + flood_lookahead;
        record->userStamp  = tt + user_lookahead;
        record->ipStamp = tt + ip_lookahead;

        //put into pQueue
        pQueue.push(make_pair(tt, record));

        //update data structures

        if(floodMap.count(record->IPaddress))
        {
            //the key is already in the map
            floodMap[record->IPaddress]++;
        }
        else
        {
            //not in map so insert
            floodMap.insert(pair<string, int>(record->IPaddress, 1));
        }

        //check if alert is triggered
        if(floodMap[record->IPaddress] > floodThreshold)
        {
            //alertAdministrator();
        }
        //expire data
        Userdata* comp_node = pQueue.top().second;
        while(currentTime > pQueue.top().first)
        {
            if(tt == comp_node->floodStamp)
            {
                //flood expire
                floodMap[record->IPaddress]--;
            }
            if(tt == comp_node->userStamp)
            {
                //user expire
            }
            if(tt == comp_node->ipStamp)
            {
                //ip expire
            }
        }
    }
    */
}

int main()
{	
    //all lookahead lengths are in seconds


    start();

    return 0;
}