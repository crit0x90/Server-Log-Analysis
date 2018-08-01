#include <iostream>
#include <string>
#include <string.h> 
#include <vector>
#include <queue>
#include <chrono>
#include <unistd.h>
#include <utility>
#include <fstream>
#include <functional>
#include "header.h"
using chrono::system_clock;
using namespace std;

//GLOBAL VARIABLES
    int lineNumber = 0;
    int alertCount = 0;
    int nodesFreed = 0;

    int fAlertCount = 0;
    int uAlertCount = 0;
    int iAlertCount = 0;
    //read via config
    int freelist_size = 0;
    int floodThreshold = 10;
    int userThreshold = 3;
    int ipThreshold = 3;
    //all lookahead lengths are in seconds
    long int flood_lookahead = 2;
    long int user_lookahead = 5;
    long int ip_lookahead = 5;

typedef unsigned long int TIME_TYPE;

void readConfig()
{
    populateMonthMap();
    populateReverseMonthMap();
    populateDaycountMap();
    string line;
    int value = 0;
    int counter = 1;
    int start_index;
    int end_index;
    string::size_type sz;
    ifstream config("config.txt");
    if(config.is_open())
    {
        while(getline(config, line))
        {   
            if(line.size() > 0 && line.at(0) != '#')
            {
                //cout << "line recieved: " << line << endl;
                for(int i = 0; i < line.size(); i++)
                {
                    if(line.at(i) == ':')
                    {
                        start_index = i+1;
                    }
                    if(line.at(i) == ';')
                    {
                        end_index = i;
                    }
                }
                //numerical value for the variable recieved
                value = stoi(line.substr(start_index, end_index-start_index), &sz);
                //cout << value << endl;

                //if a variable is added later it must be registered in this switch
                switch(counter)
                {
                    case 1: freelist_size = value;
                            counter++;
                            break;

                    case 2: floodThreshold = value;
                            counter++;
                            break;

                    case 3: userThreshold = value;
                            counter++;
                            break;

                    case 4: ipThreshold = value;
                            counter++;
                            break;

                    case 5: flood_lookahead = value;
                            counter++;
                            break;

                    case 6: user_lookahead = value;
                            counter++;
                            break;

                    case 7: ip_lookahead = value;
                            counter++;
                            break;

                    default:
                            cerr << "Error in switch statement for config read" << endl; 
                            break;
                }
            }
        }
        config.close();
    }
    else
    {
        cerr << "ERROR: UNABLE TO OPEN CONFIG FILE" << endl;
    }

    cout << "freelist_size: " << freelist_size << endl;

    cout << "floodThreshold: " << floodThreshold << endl;
    cout << "userThreshold: " << userThreshold << endl;
    cout << "ipThreshold: " << ipThreshold << endl;

    cout << "flood_lookahead: " << flood_lookahead << endl;
    cout << "user_lookahead: " << user_lookahead << endl;
    cout << "ip_lookahead: " << ip_lookahead << endl;
}

//custom comparator for the priority queue
bool pair_greater(pair<TIME_TYPE, Userdata*> a, pair<TIME_TYPE, Userdata*> b)
{
    if(a.first > b.first)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void start()
{
    cout << "Starting execution" << endl;
    string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:38 -0700]";

    //DATA STRUCTURES
    Freelist* freelist = new Freelist(freelist_size); //freelist
    
    //priority queue for expiring data
    priority_queue<pair<TIME_TYPE, Userdata*>, vector<pair<TIME_TYPE, Userdata*> >,\
     function<bool(pair<TIME_TYPE, Userdata*> , pair<TIME_TYPE, Userdata*>)> > pQueue(pair_greater);

    map<string, int> floodMap; //flood map
    map<string, map<string, TIME_TYPE> > ipMap; //ip map, ip -> map<usr, expr time>
    map<string, map<string, TIME_TYPE> > userMap; //user map, username -> map<ip, expr time>
    
    string lineInput;
    TIME_TYPE currentWorkingTime;
    
    while (getline(cin,lineInput))
    {      
        currentWorkingTime = toTimeType(lineInput);

        lineNumber++;

    //set record info
        //cout << "Setting record info" << endl;
        Userdata* record = freelist->getNode(testLine); //no timestamps yet
        record->floodStamp = incrementTimeStamp(currentWorkingTime, flood_lookahead);
        record->userStamp  = incrementTimeStamp(currentWorkingTime, user_lookahead);
        record->ipStamp = incrementTimeStamp(currentWorkingTime, ip_lookahead);

    //put in queue
        //cout << "Queueing data" << endl;
        pQueue.push(make_pair(record->floodStamp, record));
        pQueue.push(make_pair(record->userStamp, record));
        pQueue.push(make_pair(record->ipStamp, record));

    //update data structures
        //cout << "Updating data structures" << endl;
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

        //update ip map
        ipMap[record->IPaddress][record->username] = currentWorkingTime;

        //update user map
        userMap[record->username][record->IPaddress] = currentWorkingTime;

    //check if alert is triggered
        //cout << "Checking for alert triggers" << endl;
        if(floodMap[record->IPaddress] > floodThreshold)
        {
            alertCount++;
            fAlertCount++;
            cout << "ALERTING ADMINISTRATOR: FLOODING" << endl;
            cout << "Line number: " << lineNumber << endl;
            cout << "Username: " << record->username << endl;
            cout << "IPaddress: " << record->IPaddress << endl;
            cout << "Timestamp: " << toReadableTime(record->floodStamp) << endl;

            floodMap[record->IPaddress] = 0;
            alertAdministrator(make_tuple("FLOODING", lineNumber, record->username, record->IPaddress, record->floodStamp));
        }

        if(ipMap[record->IPaddress].size() > ipThreshold)
        {
            iAlertCount++;
            alertCount++;
            cout << "ALERTING ADMINISTRATOR: IP" << endl;
            cout << "Line number: " << lineNumber << endl;
            cout << "Username: " << record->username << endl;
            cout << "IPaddress: " << record->IPaddress << endl;
            cout << "Timestamp: " << toReadableTime(record->ipStamp) << endl;
            ipMap.erase(record->IPaddress);   
            alertAdministrator(make_tuple("IP", lineNumber, record->username, record->IPaddress, record->floodStamp));
        }

        if(userMap[record->username].size() > userThreshold)
        {
            uAlertCount++;
            alertCount++;
            cout << "ALERTING ADMINISTRATOR: USERNAME" << endl;
            cout << "Line number: " << lineNumber << endl;
            cout << "Username: " << record->username << endl;
            cout << "IPaddress " << record->IPaddress << endl;            
            cout << "Timestamp: " << toReadableTime(record->userStamp) << endl;
            ipMap.erase(record->IPaddress);
            alertAdministrator(make_tuple("USERNAME", lineNumber, record->username, record->IPaddress, record->floodStamp));
        }

    //expire data
        Userdata* comp_node;
        while(currentWorkingTime >= pQueue.top().first)
        {
            //cout << "Expiring data" << endl;
            comp_node = pQueue.top().second;

            //flood expire
            if(currentWorkingTime >= comp_node->floodStamp)
            {
                floodMap[record->IPaddress]--;
                //cout << comp_node->floodStamp << endl;
                comp_node->floodStamp = -1;

                //if no unexpired data left return to free list
                if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
                {
                    //cout << "Freeing Node" << endl;
                    nodesFreed++;
                    freeNode(comp_node); //resets node data
                    //put back on free list
                    comp_node->free_next = freelist->freelist_head;
                    freelist->freelist_head = comp_node;
                }
            }

            //ip expire
            if(currentWorkingTime >= comp_node->ipStamp)
            {
                //if the current nodes ip timestamp is the same as the most recent time
                //stamp on that nodes user in the ip map then expire that user
                comp_node->ipStamp = -1;

                if(comp_node->ipStamp == ipMap[comp_node->IPaddress][comp_node->username])
                {
                    ipMap[record->IPaddress].erase(comp_node->username);
                }

                //if no unexpired data left return to free list
                if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
                {
                    nodesFreed++;
                    //cout << "Freeing Node" << endl;
                    freeNode(comp_node); //resets node data
                    //put back on free list
                    comp_node->free_next = freelist->freelist_head;
                    freelist->freelist_head = comp_node;
                }
            }

            //user expire
            if(currentWorkingTime >= comp_node->userStamp)
            {   
                //if the current nodes user timestamp is the same as the most recent time
                //stamp on that nodes ip address in the user map, then expire that ip
                comp_node->userStamp = -1;

                if(comp_node->userStamp == ipMap[comp_node->username][comp_node->IPaddress])
                {
                    ipMap[record->username].erase(comp_node->IPaddress);
                }

                //if no unexpired data left return to free list
                if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
                {
                    nodesFreed++;
                    //cout << "Freeing Node" << endl;
                    freeNode(comp_node); //resets node data
                    //put back on free list
                    comp_node->free_next = freelist->freelist_head;
                    freelist->freelist_head = comp_node;
                }
            }
            pQueue.pop();
        }
    }
    
    cout << "Nodes freed: " << nodesFreed << endl;
    cout << "Total alerts sent: " << alertCount << endl;
    cout << "flood alerts sent: " << fAlertCount << endl;
    cout << "User alerts sent: " << uAlertCount << endl;
    cout << "IP alerts sent: " << iAlertCount << endl;
}

void prewrittenStart(string filename)
{
    cout << "Starting execution" << endl;

    //DATA STRUCTURES
    Freelist* freelist = new Freelist(freelist_size); //freelist
    
    //priority queue for expiring data
    priority_queue<pair<TIME_TYPE, Userdata*>, vector<pair<TIME_TYPE, Userdata*> >,\
     function<bool(pair<TIME_TYPE, Userdata*> , pair<TIME_TYPE, Userdata*>)> > pQueue(pair_greater);

    map<string, int> floodMap; //flood map
    map<string, map<string, TIME_TYPE> > ipMap; //ip map, ip -> map<usr, expr time>
    map<string, map<string, TIME_TYPE> > userMap; //user map, username -> map<ip, expr time>
    
    string lineInput;
    ifstream inputfile(filename);
    TIME_TYPE currentWorkingTime;


    if(inputfile)
    {
        while (getline(inputfile,lineInput))
        {      
            lineNumber++;
            if(lineInput == "")
            {
                continue;
            }
            currentWorkingTime = toTimeType(lineInput);

        //set record info
            //cout << "Setting record info" << endl;
            Userdata* record = freelist->getNode(lineInput); //no timestamps yet
            record->floodStamp = incrementTimeStamp(currentWorkingTime, flood_lookahead);
            record->userStamp  = incrementTimeStamp(currentWorkingTime, user_lookahead);
            record->ipStamp = incrementTimeStamp(currentWorkingTime, ip_lookahead);

        //put in queue
            //cout << "Queueing data" << endl;
            pQueue.push(make_pair(record->floodStamp, record));
            pQueue.push(make_pair(record->userStamp, record));
            pQueue.push(make_pair(record->ipStamp, record));

        //update data structures
            //cout << "Updating data structures" << endl;
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

            //update ip map
            ipMap[record->IPaddress][record->username] = currentWorkingTime;

            //update user map
            userMap[record->username][record->IPaddress] = currentWorkingTime;

        //check if alert is triggered
            //cout << "Checking for alert triggers" << endl;
            if(floodMap[record->IPaddress] > floodThreshold)
            {
                alertCount++;
                fAlertCount++;
                cout << "ALERTING ADMINISTRATOR: FLOODING" << endl;
                cout << "Line number: " << lineNumber << endl;
                cout << "Username: " << record->username << endl;
                cout << "IPaddress: " << record->IPaddress << endl;
                cout << "Timestamp: " << toReadableTime(record->floodStamp) << endl;

                floodMap[record->IPaddress] = 0;
                alertAdministrator(make_tuple("FLOODING", lineNumber, record->username, record->IPaddress, record->floodStamp));
            }

            if(ipMap[record->IPaddress].size() > ipThreshold)
            {
                iAlertCount++;
                alertCount++;
                cout << "ALERTING ADMINISTRATOR: IP" << endl;
                cout << "Line number: " << lineNumber << endl;
                cout << "Username: " << record->username << endl;
                cout << "IPaddress: " << record->IPaddress << endl;
                cout << "Timestamp: " << toReadableTime(record->ipStamp) << endl;
                ipMap.erase(record->IPaddress);   
                alertAdministrator(make_tuple("IP", lineNumber, record->username, record->IPaddress, record->floodStamp));
            }

            if(userMap[record->username].size() > userThreshold)
            {
                uAlertCount++;
                alertCount++;
                cout << "ALERTING ADMINISTRATOR: USERNAME" << endl;
                cout << "Line number: " << lineNumber << endl;
                cout << "Username: " << record->username << endl;
                cout << "IPaddress " << record->IPaddress << endl;            
                cout << "Timestamp: " << toReadableTime(record->userStamp) << endl;
                ipMap.erase(record->IPaddress);
                alertAdministrator(make_tuple("USERNAME", lineNumber, record->username, record->IPaddress, record->floodStamp));
            }

        //expire data
            Userdata* comp_node;
            while(currentWorkingTime >= pQueue.top().first)
            {
                //cout << "Expiring data" << endl;
                comp_node = pQueue.top().second;

                //flood expire
                if(currentWorkingTime >= comp_node->floodStamp)
                {
                    floodMap[record->IPaddress]--;
                    //cout << comp_node->floodStamp << endl;
                    comp_node->floodStamp = -1;

                    //if no unexpired data left return to free list
                    if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
                    {
                        //cout << "Freeing Node" << endl;
                        nodesFreed++;
                        freeNode(comp_node); //resets node data
                        //put back on free list
                        comp_node->free_next = freelist->freelist_head;
                        freelist->freelist_head = comp_node;
                    }
                }

                //ip expire
                if(currentWorkingTime >= comp_node->ipStamp)
                {
                    //if the current nodes ip timestamp is the same as the most recent time
                    //stamp on that nodes user in the ip map then expire that user
                    comp_node->ipStamp = -1;

                    if(comp_node->ipStamp == ipMap[comp_node->IPaddress][comp_node->username])
                    {
                        ipMap[record->IPaddress].erase(comp_node->username);
                    }

                    //if no unexpired data left return to free list
                    if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
                    {
                        nodesFreed++;
                        //cout << "Freeing Node" << endl;
                        freeNode(comp_node); //resets node data
                        //put back on free list
                        comp_node->free_next = freelist->freelist_head;
                        freelist->freelist_head = comp_node;
                    }
                }

                //user expire
                if(currentWorkingTime >= comp_node->userStamp)
                {   
                    //if the current nodes user timestamp is the same as the most recent time
                    //stamp on that nodes ip address in the user map, then expire that ip
                    comp_node->userStamp = -1;

                    if(comp_node->userStamp == ipMap[comp_node->username][comp_node->IPaddress])
                    {
                        ipMap[record->username].erase(comp_node->IPaddress);
                    }

                    //if no unexpired data left return to free list
                    if(comp_node->floodStamp < 0 && comp_node->userStamp < 0 && comp_node->ipStamp < 0)
                    {
                        nodesFreed++;
                        //cout << "Freeing Node" << endl;
                        freeNode(comp_node); //resets node data
                        //put back on free list
                        comp_node->free_next = freelist->freelist_head;
                        freelist->freelist_head = comp_node;
                    }
                }
                pQueue.pop();
            }
        }
        inputfile.close();
    }
    
    cout << "Nodes freed: " << nodesFreed << endl;
    cout << "Total alerts sent: " << alertCount << endl;
    cout << "flood alerts sent: " << fAlertCount << endl;
    cout << "User alerts sent: " << uAlertCount << endl;
    cout << "IP alerts sent: " << iAlertCount << endl;


}

int main(int argc, char **argv)
{	
    readConfig();

    //here we want to be able to specify a flag for a prewritten log file
    //i.e. if flag then open/read file, else then start()

    if(argc > 1)
    {   
        if(!(strcmp(argv[1], "-p")) || !(strcmp(argv[1], "--prewritten")))
        {   
            cout << "Running analysis on file " << argv[2] << endl;
            prewrittenStart(argv[2]);
        }   
        else
        {
            cout << "ERROR: Incorrect command usage" << endl;
            cout << "Correct usage: ./drive [-options] [input-file]" << endl;
        }
    }    
    else
    {
        start();    
    }
    

    return 0;
}