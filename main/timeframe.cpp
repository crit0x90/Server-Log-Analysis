#include <iostream>
#include <string>
#include "header.h"

using namespace std;

Timeframe::Timeframe()
{
	timeArray = new Userdata[86400];

	freelist_head  = new Userdata;
	Userdata* curr = freelist_head;

	//start the free list as 20,000 nodes
	for(int i = 0; i < 20000; i++)
	{
		curr->free_next = new Userdata;
	}
}

void Timeframe::appendNode(string request)
{

	int index = getIndex(request);
	string IP = getIP(request); 
	string name = getName(request);

	//check if we need to expire nodes
	if(index != currentIndex)
	{
		if(index > currentIndex)
		{
			for(int i = currentIndex; i <= index; i++)
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
	
	//if free list is empty then make a new node, 
	//else pull a node from the freelist
	if(freelist_head == nullptr)
	{
		Userdata* node = new Userdata(name, IP);
		
		//if there is an element in the array slot then insert,
		//else use seperate chaining
		if(timeArray[index].time_next == nullptr)
		{
			cout << "yeet";
			//timeArray[index].time_next = node;
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
		while(curr->time_next != nullptr)
		{
			curr->username  = "NULLPTR";
			curr->IPaddress = "NULLPTR";
			curr->IP_next   = nullptr;
			curr->user_next = nullptr;
			curr->time_next = nullptr;
			curr->free_next = freelist_head;
			freelist_head   = curr;
		}
		curr->username  = "NULLPTR";
		curr->IPaddress = "NULLPTR";
		curr->IP_next   = nullptr;
		curr->user_next = nullptr;
		curr->time_next = nullptr;
		curr->free_next = freelist_head;
		freelist_head   = curr;
	}
}