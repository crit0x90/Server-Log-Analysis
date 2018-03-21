#include <iostream>
#include <string>
#include <unistd.h>
#include "header.h"

using namespace std;

Timeframe::Timeframe()
{
	timeArray = new Userdata[86400];

	freelist_head  = new Userdata;
	Userdata* curr = freelist_head;
	currentIndex = 0;

	//start the free list as 20,000 nodes
	for(int i = 0; i < 20000; i++)
	{
		curr->free_next = new Userdata;
		curr = curr->free_next;
	}
}

void Timeframe::appendNode(string request)
{

	int newindex = getIndex(request);
	string IP = getIP(request); 
	string name = getName(request);
	/*
	cout << request << endl;
	cout << "index: " << index << endl;
	cout << "IP: " << IP << endl;
	cout << "name: " << name << endl;
	*/

	//check if we need to expire nodes
	if(newindex != currentIndex)
	{
		if(newindex > currentIndex)
		{
			//expire everything between what we just inserted
			//and what we want to insert
			for(int i = currentIndex+1; i <= newindex; i++)
			{
				expireFrame(i);
			}
		}
		else
		{
			//we need to loop back around the ring in this case 
			//(new day has started)
			for(int i = currentIndex; i <= 86399; i++)
			{
				expireFrame(i);
			}

			for(int i = 0; i <= newindex; i++)
			{
				expireFrame(i);
			}
		}
	}
	
	currentIndex = newindex;
	
	//if free list is empty then make a new node, 
	//else pull a node from the freelist
	if(freelist_head->free_next == nullptr)
	{
		Userdata* node = new Userdata(name, IP);
		
		//if there is an element in the array slot then insert,
		//else use seperate chaining
		if(timeArray[newindex].time_next == nullptr)
		{
			timeArray[newindex].time_next = node;
		}
		else
		{
			Userdata* curr = &(timeArray[newindex]);
			while(curr->time_next != nullptr)
			{
				curr = curr->time_next;
			}
			curr->time_next = node;
		}
		timeArray[newindex].floodCounter++;
	}
	else
	{
		//if there is an element in the array slot then insert,
		//else use seperate chaining
		Userdata* node = freelist_head;

		//multiple nodes or single node on free list
		if(freelist_head->free_next != nullptr)
		{
			freelist_head = freelist_head->free_next;
		}
		else
		{
			freelist_head = nullptr;
		}

		//no nodes in slice or there are nodes in slice
		if(timeArray[newindex].time_next == nullptr)
		{
			timeArray[newindex].time_next = node;
		}
		else
		{
			Userdata* curr = &(timeArray[newindex]);
			while(curr->time_next != nullptr)
			{
				//cout << "Stuck at index" << newindex << "[appendNode()]" << endl;
				curr = curr->time_next;
			}
			curr->time_next = node;
		}
		timeArray[newindex].floodCounter++;
	}
	//cout << "Flood counter at: " << timeArray[newindex].floodCounter << endl;
	if(timeArray[newindex].floodCounter > 10)
	{
		//we will want to make this check for a single user in the time frame in the future
		alertAdministrator("Request flood", newindex);
	}
}

void Timeframe::expireFrame(int index)
{
	if(timeArray[index].time_next == nullptr)
	{
		return;
	}
	else 
	{
		cout << "Expiring data" << endl;
		//not empty case
		timeArray[index].floodCounter = 0;
		Userdata* curr = &(timeArray[index]);

		//This is tricky here, we start at a non-node so
		//even though it seems like we are missing the 
		//one node case we are not
		while(curr->time_next != nullptr)
		{
			Userdata* nextNode = curr->time_next; //placeholder

			curr->username  = "NULLPTR";
			curr->IPaddress = "NULLPTR";
			curr->IP_next   = nullptr;
			curr->user_next = nullptr;
			curr->time_next = nullptr;
			curr->free_next = freelist_head;
			freelist_head   = curr;
			curr = nextNode;
		}
		//so that the last node isn't orphaned
		curr->username  = "NULLPTR";
		curr->IPaddress = "NULLPTR";
		curr->IP_next   = nullptr;
		curr->user_next = nullptr;
		curr->time_next = nullptr;
		curr->free_next = freelist_head;
		freelist_head   = curr;

		timeArray[index].time_next = nullptr;
	}
}

int Timeframe::lenFreeList()
{
	Userdata* curr = freelist_head;

	int counter = 0;

	while(curr->free_next != nullptr)
	{
		curr = curr->free_next;
		counter++;
	}
	return counter;
}

void Timeframe::clearAllFrames()
{
	for(int i = 0; i < 86400; i++)
	{
		expireFrame(i);
	}
}

void Timeframe::alertAdministrator(string reason, int index)
{
	cout << "Alerting the administrator because " << reason << " at timeindex " << index << endl;
	sleep(3);
}