#ifndef HEADER_H
#define HEADER_H

#include <string>

using namespace std;

class Userdata {
public:
	string username;
	string IPaddress;
private:
protected:
};

class Timeslice {
public:
	Userdata* timeArray;
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

//returns an index given a raw string
int getIndex(string raw_line);

//splits a string apart at the spaces and returns a vector
vector<string> splitVector(string data);

#endif