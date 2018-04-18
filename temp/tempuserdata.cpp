#include <iostream> 
#include "newheader.h"

using namespace std;

chrono::system_clock::duration LOOKAHEAD_LENGTH;

Userdata::Userdata(string name, string IP)
{
	username = name;
	IPaddress = IP;

	expirationTime = 0;
}

void readConfig()
{
	const long int seconds = 40;
	LOOKAHEAD_LENGTH = chrono::duration<int, ratio<seconds> > (1);
}