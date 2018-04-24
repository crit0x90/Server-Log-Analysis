#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <chrono>
#include <unistd.h>
using namespace std;
using chrono::system_clock;

/*
	GOALS FOR THIS DATA STRUCTURE

	-count the number of requests coming in in a small
	 amount of time (indicative of spidering/scripted 
	 traversal, DoS, mass download script)

	-count the number IP addresses associated with each
	 username

	-count the number of usernames associated with each
	 IP address

	-expire each piece of information at the appropriate 
	 time
*/


class Userdata {
public:
	Userdata() {}
	Userdata(string name, string IP);
	~Userdata() {}

	string username;
	string IPaddress;
	//time_t can be treated like a long int
	time_t t;
private:
protected:
};

void readConfig();


class Freelist {
public:
	Freelist() {}
	Freelist(int size);
	~Freelist() {}
	//returns a node ready for insertion in qQueue
	Userdata* getNode(string raw_line); 
	Userdata* getFreelistHead();
private:
	Userdata* freelist_head;
protected:
};
/*
class Timeframe {
public:
	//priority queue that puts the lowest priority first, used for expiration
	//of data, satisfies goal 4
	priority_queue<int, vector<int>, greater<int> > pQueue;

	//checks if the IP has made too many requests in the last x seconds
	//satisfies goal 1
	map<string IP, int appearances> flood_map;

	//keeps track of the IPs associated with each user
	//satisfies goal 2
	map<string username, pair<string IP, int occurrences> > user_to_IP_map;

	//keeps track of the users associated with each IP
	//satisfies goal 3
	map<string IP, pair<string username, int occurrences> > IP_to_user_map;
private:
	//how long we will wait to expire each value
	int USER_LOOKAHEAD_LENGTH;
	int IP_LOOKAHEAD_LENGTH;
	//so that the freelist is accessible
	Freelist* freelist;
protected:
};

#endif