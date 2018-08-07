#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <chrono>
#include <unistd.h>

using namespace std;

typedef long int TIME_TYPE;

class Userdata {
public:
	Userdata();
	Userdata(string name, string IP);
	~Userdata() {}

	string username;
	string IPaddress;
	int nodeNumber;

	Userdata* free_next;

	TIME_TYPE floodStamp;
	TIME_TYPE userStamp;
	TIME_TYPE ipStamp;
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

//splits a string apart at the spaces and returns a vector
vector<string> splitVector(string data);

//returns a username given a raw input string
string getName(string raw_line);

//returns an IP address given a raw input string
string getIP(string raw_line);

//clears out the value fields of a node
void freeNode(Userdata* node);

//sends the administrator the report
void alertAdministrator(tuple<string, int, string, string, TIME_TYPE> t);

//for use with incrementTimeStamp
void populateMonthMap();

//for use with incrementTimeStamp
void populateReverseMonthMap();

//for use with incrementTimeStamp
void populateDaycountMap();

//extracts time from line and converts into numerical representation
TIME_TYPE toTimeType(string raw_line);

//converts time_type back to human readable format
string toReadableTime(TIME_TYPE integerTime);

//increments the timestamp 
TIME_TYPE incrementTimeStamp(TIME_TYPE old_stamp, long int lookahead);

#endif