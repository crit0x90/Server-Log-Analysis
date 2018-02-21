#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

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