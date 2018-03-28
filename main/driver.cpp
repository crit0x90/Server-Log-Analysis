#include <iostream>
#include <string>
#include <vector>
#include "header.h"
using namespace std;

void start(int tf_size)
{
    Timeframe* timeframe = new Timeframe(tf_size);

    string lineInput;
    int counter = 0;
    int index = 0;
    while (getline(cin,lineInput)) 
    {
        timeframe->insertData(lineInput);
        counter++;
    }
}

int main()
{	
    start(30);

    return 0;
}