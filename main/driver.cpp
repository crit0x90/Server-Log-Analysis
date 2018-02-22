#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "header.h"
using namespace std;


vector<string> splitVector(string data)
{
	//initialization
	typedef vector<string> split_vector_type;
    
    //splits the string
    split_vector_type splitVec; 
    boost::split( splitVec, data, boost::is_any_of(" "), boost::token_compress_on );

    return splitVec;
}

int main()
{	
	/*
	string lineInput;
	while (getline(cin,lineInput)) 
	{
  		cout << "***" << lineInput;
	}
	*/

	string str1 = "IP1293 [-] - [04/Sep/2017:00:13:49 -0700]"; //sample string for testing
	string time = "";

	vector<string> splitVec = splitVector(str1);

    //gets time from string in hours:minutes:seconds format
    time =  getTime(splitVec.at(3));
    cout << "Time: " << time << endl;

    //extract values for hours and minutes and convert to int to be used as indexes
    int hours   = getHours(time);
    int minutes = getMinutes(time);

    cout << hours << ", " << minutes << endl;
	
	hourRing* ring_chain = new hourRing;

	ring_chain->mainring[0].datalist[0].append("cat");
    cout << ring_chain->mainring[0].datalist[0].head->name << endl;
    
	return 0;
}