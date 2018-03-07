#include <iostream>
#include <string>
#include <vector>
#include "header.h"
using namespace std;

int main()
{	
	/*
	string lineInput;
	while (getline(cin,lineInput)) 
	{
  		cout << "***" << lineInput;
	}
	*/

	string str1 = "IP1293 [-] realname [04/Sep/2017:00:13:49 -0700]"; //sample string for testing

    Timeframe* timeframe = new Timeframe;

    for(int i = 0; i < 25,000; i++)
    {
    	timeframe->appendNode(str1);	
    }

    timeframe->expireFrame(829);


	return 0;
}