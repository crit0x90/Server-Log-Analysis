#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "header.h"
using namespace std;

int getHours(string time)
{
	int hours = -1;
	try 
	{
		cout << time.substr(0,2) << endl;
    	hours = boost::lexical_cast<int>(time.substr(0,2));
	} 	
	catch( boost::bad_lexical_cast const& ) 
	{
    	cout << "Error: input string was not valid" << endl;
	}
	return hours;
}

int getMinutes(string time)
{
	int minutes = -1;
	try 
	{
		cout << time.substr(3,2) << endl;
    	minutes = boost::lexical_cast<int>(time.substr(3,2));
	} 	
	catch( boost::bad_lexical_cast const& ) 
	{
    	cout << "Error: input string was not valid" << endl;
	}
	return minutes;
}

string getTime(string in)
{
	in = in.substr(13, 20); // hours:minutes:seconds	
	return in;
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

	typedef vector<string> split_vector_type;
	string str1 = "IP1293 [-] - [04/Sep/2017:00:13:49 -0700]"; //sample string for testing
	string time = "garbage";
    
    split_vector_type splitVec; 
    boost::split( splitVec, str1, boost::is_any_of(" "), boost::token_compress_on );

    time =  getTime(splitVec.at(3));
    cout << "Time: " << time << endl;

    int hours   = getHours(time);
    int minutes = getMinutes(time);

    cout << hours << ", " << minutes << endl;


    
    


	return 0;
}