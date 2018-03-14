#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include "../testing/testing.h"
using namespace std;

int main()
{	

	string str1 = "IP1293 [-] realname [04/Sep/2017:00:13:49 -0700]"; //sample string for testing

    Timeframe* timeframe = new Timeframe;

    string lineInput;
    int counter = 0;

    while (getline(cin,lineInput)) 
	{
		counter++;
  		timeframe->appendNode(lineInput);
  		cout << counter << endl;
	}

	return 0;
}