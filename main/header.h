#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>

using namespace std;

class Userdata {
public:
	Userdata();
	Userdata(string name, string IP);
	~Userdata() {}

	//number of requests in current time slice, only to be used by 
	//the node that is in the timeArray
	int IPcounter; //for users
	int userCounter; //for IPs
	string username;
	string IPaddress;
	Userdata* IP_next;
	Userdata* user_next;
	Userdata* time_next;
	Userdata* free_next;
private:
protected:
};


class Freelist {
public:
	Freelist() {}
	Freelist(int size);
	~Freelist() {}
	Userdata* getNode(string raw_line);
	Userdata* getFreelistHead();
private:
	Userdata* freelist_head;
protected:
};


class Timeframe {
public:
	Timeframe() {}
	Timeframe(int size);
	~Timeframe() {}
	void insertData(Userdata* node, int index);
private:
	//for testing
	int lenFreeList(); 

	//members that have general use for the timeframe data structure
	int currentIndex; //where we are currently operating in the timeframe DS
	void cleanup();
	void expireTimeFrame(int index);
	void expireTimeNode(Userdata* node);
	void alertAdministrator(string reason, int index);
	Userdata* timeArray; //DS used to check for expiration of data
	
	//members that deal with request flood handling
	int floodCleanupIndex; //where the cleanup index currently is for flooding
	int floodCounter; //how many requests are in the current frame
	bool floodTest(); //checks if there is one user that is causing the flooding

	//members that deal with the user hash
	Userhash* userhash;
	int userCleanupIndex;
	void expireUserFrame(int index);
	void expireUserNode(Userdata* node);

	//members that deal with the IP hash
	IPhash* iphash;
	int ipCleanupIndex;
	void expireIPFrame(int index);
	void expireIPNode(Userdata* node);

	//members that deal with the freelist
	Freelist* freelist;

	//constants that will be initialized when the data structure
	//is created but will not be changed after that
	int TIMEFRAME_SIZE;//total size of the time frame data structure
	int FLOOD_CLEANUP_LENGTH;//the distance between the floodCleanupIndex and the currentIndex
	int FLOOD_THRESHOLD; //how many requests before a flood alert is triggered
	int USER_CLEANUP_LENGTH;//the distance between the userCleanupIndex and the currentIndex
	int IP_CLEANUP_LENGTH;//the distance between the ipCleanupIndex and the currentIndex
protected:
};
//utility functions

//returns hours given a timestamp
int getHours(string time);

//returns minutes given a timestamp
int getMinutes(string time);

//returns seconds given a timestamp
int getSeconds(string time);

//returns an isolated timestamp
string getTime(string in);

//returns an index given a raw input string
int getIndex(string raw_line);

//splits a string apart at the spaces and returns a vector
vector<string> splitVector(string data);

//returns a username given a raw input string
string getName(string raw_line);

//returns an IP address given a raw input string
string getIP(string raw_line);

#endif