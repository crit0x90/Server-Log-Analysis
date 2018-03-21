#include <iostream>
#include <string>
#include "header.h"

using namespace std;

Userhash::Userhash()
{
	hashSize = 20000;
	userhash = new Userdata[hashSize];
}

void Userhash::hashUser(Userdata& data)
{
	string username = data->username;
	int sum = 0;
	char x = '';
	int index = 0;

	//convert string to its ascii value
	for(int i = 0; i < username.size(); i++)
	{
		x = username.at(i);
		sum += int(x);
	}

	index = sum % hashSize;

	if(userhash[index].user_next == nullptr)
	{
		//there was no other object inserted at this index
		userhash[index].user_next = data;	
	}
	else
	{
		//there are other objects so cycle through the list
		//and look if the user is already there. If not then
		//add the user
		
	}

}