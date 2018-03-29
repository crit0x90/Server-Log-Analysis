#include <iostream>
#include <string>
#include <vector>
#include "header.h"
using namespace std;

void start(int freelist_size, int tf_size)
{
    string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:38 -0700]";

    Timeframe* timeframe = new Timeframe(tf_size);
    Freelist*  freelist = new Freelist(freelist_size);
    timeframe->insertData(freelist->getNode(testLine), 10);

    /*
    string lineInput;
    int counter = 0;
    int index = 0;
    while (getline(cin,lineInput)) 
    {
        index = getIndex(lineInput);
        timeframe->insertData(freelist->getNode(lineInput), index);
        counter++;
    }
      */
}

int main()
{	
    start(20000, 30);

    return 0;
}