#include <iostream>
#include <string>
#include <unistd.h>
#include "header.h"

using namespace std;

Timeframe::Timeframe(int floodWindowSize)
{
	//default timeframe size is one day
	TIMEFRAME_SIZE = 86400;
	FLOOD_CLEANUP_LENGTH = floodWindowSize;
	FLOOD_THRESHOLD = 6; //make this dynamic later
	USER_CLEANUP_LENGTH = 20; //make this dynamic later
	IP_CLEANUP_LENGTH = 20; //make this dynamic later

	timeArray = new Userdata[TIMEFRAME_SIZE];
	currentIndex = 0;
	floodCounter = 0;

	floodCleanupIndex = TIMEFRAME_SIZE - FLOOD_CLEANUP_LENGTH;
	userCleanupIndex  = TIMEFRAME_SIZE - USER_CLEANUP_LENGTH;
	ipCleanupIndex    = TIMEFRAME_SIZE - IP_CLEANUP_LENGTH; 
}

void Timeframe::insertData(Userdata* node, int index)
{
	cout << "Inserting data at frame index " << index << endl;

	if(timeArray[index].time_next == nullptr)
	{
		currentIndex = index;
		cleanup();
		timeArray[index].time_next = node;
	}
	else
	{
		Userdata* curr = timeArray[index].time_next; //first node in list (not meta node)

		while(curr->time_next != nullptr)
		{
			curr = curr->time_next;
		}

		curr->time_next = node;
	}

	//hash for userdata


	//hash for IP


	//increment the meta nodes flood counter
	floodCounter++;
	if(floodCounter > FLOOD_THRESHOLD)
	{
		floodTest();
	}
}

void Timeframe::cleanup()
{
	//The purpose of this function is to make the cleanupIndex
	//"catch up" to the current index whenever there is a change 
	//in the current index
	int oldFloodIndex = floodCleanupIndex;

	if(floodCleanupIndex < currentIndex)
	{
		while(floodCleanupIndex < (currentIndex - FLOOD_CLEANUP_LENGTH))
		{
			expireTimeFrame(floodCleanupIndex);
			floodCleanupIndex++;
		}
	}
	else
	{
		//this represents the case that the current index
		//has looped back around the data structure

		//total distance between currentIndex and cleanupIndex
		int totalDistance = currentIndex + (TIMEFRAME_SIZE - floodCleanupIndex);
		int distanceToTravel = totalDistance - FLOOD_CLEANUP_LENGTH;

		while(distanceToTravel > 0)
		{
			if(floodCleanupIndex == 86399)
			{
				expireTimeFrame(floodCleanupIndex);
				floodCleanupIndex = 0;
				distanceToTravel--;
			}
			else
			{
				expireTimeFrame(floodCleanupIndex);
				floodCleanupIndex++;
				distanceToTravel--;
			}
		}
	}
}

void Timeframe::expireTimeFrame(int index)
{
	cout << "Expiring time frame at index " << index << endl;

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
			placeholder = curr->time_next;
			expireTimeNode(curr);
			curr = placeholder;
		}
		//dont forget the last node
		expireTimeNode(curr);
	}
}

void Timeframe::expireTimeNode(Userdata* node)
{

	node->time_next = nullptr; //take node off out of time frame

	if(node->IP_next == nullptr && node->user_next == nullptr)
	{
		//no more relevant data is stored in this node so put 
		//it back onto the free list
		//node->free_next = getFreelistHead;
		//freelist_head = node;
		node->IPcounter = 0;
		node->userCounter = 0;
		node->username  = "Empty";
		node->IPaddress = "Empty";
	}
	floodCounter--;
}

void Timeframe::alertAdministrator(string reason, int index)
{
	cout << "Alerting the administrator: " << reason << " at index " << index << endl;
	sleep(3);
}

bool Timeframe::floodTest()
{
	bool flood_flag = false;
	cout << "Executing flood test" << endl;
	return flood_flag;
}

