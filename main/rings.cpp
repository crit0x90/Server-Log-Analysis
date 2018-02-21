#include <iostream>
#include <string>
#include "header.h"

using namespace std;


ringData::ringData()
{
	name = "garbage";
}	


dataList::dataList()
{
	curr = nullptr;
	head = nullptr;
	tail = nullptr;
}

void dataList::append(string name)
{
	if(head == nullptr)
	{
		head = new ringData;
		tail = head;
		curr = head;
		head->name = name;
	}
	else
	{
		ringData* data = new ringData;
		tail->next = data;
		data = tail;
	}	
}


minuteRing::minuteRing()
{
	//60 minutes in an hour
	datalist = new dataList[60];
}


hourRing::hourRing()
{
	//24 hours in a day
	mainring = new minuteRing[24];
}


