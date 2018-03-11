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
	~Timeframe() {}
	void appendNode(string request);
	void expireFrame(int index);
	int lenFreeList(); //for testing
	void clearAllFrames();
private:
	Userdata* timeArray;
	Userdata* freelist_head;
	int currentIndex;
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