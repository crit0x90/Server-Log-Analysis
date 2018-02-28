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
	Userdata* timeArray;
	Userdata* freelist_head;
private:
	Userdata getNode(string name, string IP);
	void freeNode(int index);
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

//returns an index given a raw string
int getIndex(string raw_line);

//splits a string apart at the spaces and returns a vector
vector<string> splitVector(string data);

#endif