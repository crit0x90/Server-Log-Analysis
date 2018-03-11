#include <iostream>
#include <string>
#include <vector>
#include "../main/header.h"

using namespace std;

bool freeListTest()
{
	//The purpose of this test is to make sure that 
	//however many nodes we put onto the data structure
	//we are also returning to the free list when they are
	//expired (memory leak test)
	Timeframe* timeframe = new Timeframe;

	string lineInput;
	int starting_length = timeframe->lenFreeList();
  	int counter = 0;
	while (getline(cin,lineInput)) 
	{
		counter++;
  		timeframe->appendNode(lineInput);
	}
	timeframe->clearAllFrames();
	int ending_length = timeframe->lenFreeList();
	bool status = (starting_length == ending_length);
  	cout << "Starting length of free list: " << starting_length << endl;
	cout << "Number of nodes inserted: " << counter << endl;
	cout << "Ending length of free list: " << ending_length << endl;
	cout << "Free list test pass: " << status << endl;

	return status;
}

bool loopAroundTest()
{
	
}