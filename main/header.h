#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <chrono>
#include <unistd.h>

using namespace std;

class Userdata {
public:
	Userdata();
	Userdata(string name, string IP);
	~Userdata() {}

	string username;
	string IPaddress;

	Userdata* free_next;

	time_t floodStamp;
	time_t userStamp;
	time_t ipStamp;
private:
protected:
};


class Freelist {
public:
	Freelist() {}
	Freelist(int size);
	~Freelist() {}
	Userdata* getNode(string raw_line);
	Userdata* freelist_head;
private:
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

//clears out the value fields of a node
void freeNode(Userdata* node);

#endif