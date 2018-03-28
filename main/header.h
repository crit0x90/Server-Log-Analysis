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
	int floodCounter; //for tracking request flooding
	int IPcounter; //for users
	int userCounter; //for IPs
	vector<string> associatedIPs;
	vector<string> associatedUsers;
	string username;
	string IPaddress;
	Userdata* IP_next;
	Userdata* user_next;
	Userdata* time_next;
	Userdata* free_next;
private:
protected:
};

class Timeframe {
public:
	Timeframe();
	Timeframe(int size);
	~Timeframe() {}
	void insertData(string raw_line);
private:
	int lenFreeList(); //for testing
	void cleanup();
	void expireFrame(int index);
	void expireNode(Userdata& node);
	void alertAdministrator(string reason, int index);
	Userdata* timeArray;
	Userdata* freelist_head;
	int currentIndex; //where we are currently operating in the timeframe DS
	int cleanupIndex; //where the cleanup index currently is
	int cleanupLength;//the distance between the cleanupIndex and the currentIndex
	int timeFrameSize;
	Userdata* getNode(string raw_line);
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