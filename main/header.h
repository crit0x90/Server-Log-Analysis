#ifndef HEADER_H
#define HEADER_H

#include <string>

using namespace std;

class ringData {
public:
	ringData();
	~ringData() {}
	string name;
	ringData* next;
private:
protected:
};


class dataList {
public:
	dataList();
	~dataList() {}
	void append(string name);
	ringData* curr;
	ringData* head;
	ringData* tail;
private:
protected:
};


class minuteRing {
public:
	minuteRing();
	~minuteRing() {}
	dataList* datalist;
private:
protected:
};

class hourRing {
public:
	hourRing();
	~hourRing() {}
	minuteRing* mainring;
private:
protected:
};


//utility functions
int getHours(string time);
int getMinutes(string time);
string getTime(string in);

#endif