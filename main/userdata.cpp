#include <iostream>
#include <string>
#include "header.h"

using namespace std;

Userdata::Userdata()
{
	username  = "NULLPTR";
	IPaddress = "NULLPTR";
	IP_next   = nullptr;
	user_next = nullptr;
	time_next = nullptr;
	free_next = nullptr;
}

Userdata::Userdata(string name, string IP)
{
	username  = name;
	IPaddress = IP;
	IP_next   = nullptr;
	user_next = nullptr;
	time_next = nullptr;
	free_next = nullptr;
}