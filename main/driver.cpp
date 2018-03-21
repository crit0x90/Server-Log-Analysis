#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include "../testing/testing.h"
using namespace std;

int main()
{	
    Timeframe* timeframe = new Timeframe;

    string lineInput;
    int counter = 0;

    while (getline(cin,lineInput)) 
  	{
    		counter++;
    		timeframe->appendNode(lineInput);
    		//cout << counter << endl;
  	}

	return 0;
}