#include <iostream>
#include <string>
#include "header.h"

Freelist::Freelist(int size)
{
	freelist_head  = new Userdata;
	Userdata* curr = freelist_head;

	//create size many nodes to start with for the free list
	for(int i = 0; i < size; i++)
	{
		curr->free_next = new Userdata;
		curr = curr->free_next;
	}
}

Userdata* Freelist::getNode(string raw_line)
{
	//this function is for getting a node off of the 
	//free list
	Userdata* node = nullptr;
	if(freelist_head == nullptr)
	{
		//freelist is empty
		node = new Userdata(getName(raw_line), getIP(raw_line));
		
	}
	else if(freelist_head->free_next == nullptr)
	{
		//freelist only hase one node left
		node = freelist_head;
		node->username  = getName(raw_line);
		node->IPaddress = getIP(raw_line);

		freelist_head = nullptr;
	}
	else
	{
		//freelist has > one node
		node = freelist_head;
		node->username  = getName(raw_line);
		node->IPaddress = getIP(raw_line);
		freelist_head = freelist_head->free_next;
	}

	return node;
}

