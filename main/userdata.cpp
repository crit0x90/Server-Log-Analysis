#include <iostream>
#include <string>
#include "header.h"

using namespace std;

Userdata::Userdata()
{
	floodCounter = 0;
	username  = "NULLPTR";
	IPaddress = "NULLPTR";
	IP_next   = nullptr;
	user_next = nullptr;
	time_next = nullptr;
	free_next = nullptr;
}

Userdata::Userdata(string name, string IP)
{
	floodCounter = 0;
	username  = name;
	IPaddress = IP;
	IP_next   = nullptr;
	user_next = nullptr;
	time_next = nullptr;
	free_next = nullptr;
}