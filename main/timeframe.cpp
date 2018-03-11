#include <iostream>
#include <string>
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

	int index = getIndex(request);
	string IP = getIP(request); 
	string name = getName(request);
	/*
	cout << request << endl;
	cout << "index: " << index << endl;
	cout << "IP: " << IP << endl;
	cout << "name: " << name << endl;
	*/

	//check if we need to expire nodes
	if(index != currentIndex)
	{
		if(index > currentIndex)
		{
			//expire everything between what we just inserted
			//and what we want to insert
			for(int i = currentIndex+1; i <= index; i++)
			{
				expireFrame(i);
			}
		}
		else
		{
			//we need to loop back around the ring in this case
			for(int i = currentIndex; i <= 86399; i++)
			{
				expireFrame(i);
			}

			for(int i = 0; i <= index; i++)
			{
				expireFrame(i);
			}
		}
	}

	currentIndex = index;
	
	//if free list is empty then make a new node, 
	//else pull a node from the freelist
	if(freelist_head == nullptr)
	{
		Userdata* node = new Userdata(name, IP);
		
		//if there is an element in the array slot then insert,
		//else use seperate chaining
		if(timeArray[index].time_next == nullptr)
		{
			timeArray[index].time_next = node;
		}
		else
		{
			Userdata* curr = &(timeArray[index]);
			while(curr->time_next != nullptr)
			{
				curr = curr->time_next;
			}
			curr->time_next = node;
		}
	}
	else
	{
		//if there is an element in the array slot then insert,
		//else use seperate chaining

		Userdata* node = freelist_head;
		if(freelist_head->free_next != nullptr)
		{
			freelist_head = freelist_head->free_next;
		}
		else
		{
			freelist_head = nullptr;
		}

		if(timeArray[index].time_next == nullptr)
		{
			timeArray[index].time_next = node;
		}
		else
		{
			Userdata* curr = &(timeArray[index]);
			while(curr->time_next != nullptr)
			{
				curr = curr->time_next;
			}
			curr->time_next = node;
		}
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
		//not empty case
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