#include <iostream>
#include <string>
#include "header.h"

using namespace std;

Timeframe::Timeframe()
{
	timeArray = new Userdata[86399];

	freelist_head  = new Userdata;
	Userdata* curr = freelist_head;

	for(int i = 0; i < 10000; i++)
	{
		curr->free_next = new Userdata;
	}
}