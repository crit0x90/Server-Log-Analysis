#include <iostream>
#include <string>
#include <unistd.h>
#include "header.h"

using namespace std;

Timeframe::Timeframe()
{
	//default timeframe size is one day
	timeFrameSize = 86400;
	timeArray = new Userdata[timeFrameSize];

	freelist_head  = new Userdata;
	Userdata* curr = freelist_head;
	currentIndex = 0;
	cleanupLength = 20;
	//default cleanup size is 20 seconds
	cleanupIndex = timeFrameSize - 20; 

	//start the free list as 20,000 nodes
	for(int i = 0; i < 20000; i++)
	{
		curr->free_next = new Userdata;
		curr = curr->free_next;
	}
}

Timeframe::Timeframe(int size)
{
	//default timeframe size is one day
	timeFrameSize = 86400;
	timeArray = new Userdata[timeFrameSize];

	freelist_head  = new Userdata;
	Userdata* curr = freelist_head;
	currentIndex = 0;
	cleanupLength = size;
	//the length of time before cleanup is called 
	//is represented by maxsize - size
	cleanupIndex = timeFrameSize - cleanupLength;

	//start the free list as 20,000 nodes
	for(int i = 0; i < 20000; i++)
	{
		curr->free_next = new Userdata;
		curr = curr->free_next;
	}
}

void Timeframe::insertData(string raw_line)
{
	int index = getIndex(raw_line);
	cout << "Inserting data at frame index " << index << endl;

	if(index != currentIndex)
	{
		currentIndex = index;
		cleanup();
		timeArray[index].time_next = getNode(raw_line);
	}
	else
	{
		//since we are on this branch we know that the
		//current index has not changed since the last
		//time that we went to insert a node so we can
		//infer that there is already a node at the 
		//current index
		Userdata* curr = timeArray[index].time_next;

		while(curr->time_next != nullptr)
		{
			curr = curr->time_next;
		}

		curr->time_next = getNode(raw_line);
	}
}

void Timeframe::cleanup()
{
	//The purpose of this function is to make the cleanupIndex
	//"catch up" to the current index whenever there is a change 
	//in the current index
	int oldCleanupIndex = cleanupIndex;
	if(cleanupIndex < currentIndex)
	{
		while(cleanupIndex < (currentIndex - cleanupLength))
		{
			expireFrame(cleanupIndex);
			cleanupIndex++;
		}
	}
	else
	{
		//this represents the case that the current index
		//has looped back around the data structure

		//total distance between currentIndex and cleanupIndex
		int totalDistance = currentIndex + (timeFrameSize - cleanupIndex);
		int distanceToTravel = totalDistance - cleanupLength;

		while(distanceToTravel > 0)
		{
			if(cleanupIndex == 86399)
			{
				expireFrame(cleanupIndex);
				cleanupIndex = 0;
				distanceToTravel--;
			}
			else
			{
				expireFrame(cleanupIndex);
				cleanupIndex++;
				distanceToTravel--;
			}
		}
	}
}

void Timeframe::expireFrame(int index)
{
	cout << "Expiring frame at index " << index << endl;

	if(timeArray[index].time_next == nullptr)
	{
		//empty case - nothing is stored at this index
	}
	else
	{
		Userdata* curr = timeArray[index].time_next; //curr == first node in list
		timeArray[index].time_next = nullptr; //point the array pointer back to null
		Userdata* placeholder = nullptr;

		while(curr->time_next != nullptr)
		{
			cout << "Old value: " << curr->username << endl;
			placeholder = curr->time_next;
			expireNode(curr);
			freelist_head = curr;
			curr = placeholder;
			cout << "New value: " << curr->username << endl;
		}
		//dont forget the last node
		expireNode(curr);
		freelist_head = curr;
	}
}

void Timeframe::expireNode(Userdata& node)
{
	/*
	node->username  = "EMPTY";
	node->IPaddress = "EMPTY";
	node->IP_next = nullptr;
	node->user_next = nullptr;
	node->time_next = nullptr;
	node->free_next = freelist_head;
	*/
}

void Timeframe::alertAdministrator(string reason, int index)
{
	cout << "Alerting the administrator: " << reason << " at timeindex " << index << endl;
	sleep(3);
}

Userdata* Timeframe::getNode(string raw_line)
{
	//this function is for getting a node off of the 
	//free list
	Userdata* node = nullptr;
	if(freelist_head == nullptr)
	{
		//freelist is empty
		node = new Userdata();
	}
	else if(freelist_head->free_next == nullptr)
	{
		//freelist only hase one node left
		node = freelist_head;
		freelist_head = nullptr;
	}
	else
	{
		//freelist has > one node
		node = freelist_head;
		freelist_head = freelist_head->free_next;
	}

	return node;
}