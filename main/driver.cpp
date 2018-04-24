#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <chrono>
#include <unistd.h>
#include <utility>
#include "header.h"
using chrono::system_clock;
using namespace std;

int floodThreshold = 10;
int freelist_size = 0;
int flood_lookahead = 0;
int user_lookahead = 0;
int ip_lookahead = 0;

void start()
{
    string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:38 -0700]";

    Freelist* freelist = new Freelist(freelist_size); //freelist
    priority_queue<pair<time_t, Userdata*> > pQueue;  //priority queue
    map<string, int> floodMap;//floodMap

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

    cout << "floodMap: " << floodMap[record->IPaddress] << endl;

    //check if alert is triggered
    if(floodMap[record->IPaddress] > floodThreshold)
    {
        //alertAdministrator();
    }

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

        //expire data
    }
    */
}

int main()
{	
    //all lookahead lengths are in seconds


    start();

    return 0;
}