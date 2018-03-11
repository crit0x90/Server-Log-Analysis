#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

int getHours(string time)
{
	int hours = -1;
	try 
	{
		//cout << time.substr(0,2) << endl;
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
		//cout << time.substr(3,2) << endl;
    	minutes = boost::lexical_cast<int>(time.substr(3,2));
	} 	
	catch( boost::bad_lexical_cast const& ) 
	{
    	cout << "Error: input string was not valid" << endl;
	}
	return minutes;
}

int getSeconds(string time)
{
	int seconds = -1;
	try 
	{
		//cout << time.substr(6,2) << endl;
    	seconds = boost::lexical_cast<int>(time.substr(6,2));
	} 	
	catch( boost::bad_lexical_cast const& ) 
	{
    	cout << "Error: input string was not valid" << endl;
	}
	return seconds;
}

string getTime(string in)
{
	in = in.substr(13, 20); // hours:minutes:seconds	
	return in;
}

vector<string> splitVector(string data)
{
	//initialization
	typedef vector<string> split_vector_type;
    
    //splits the string
    split_vector_type splitVec;
    boost::split( splitVec, data, boost::is_any_of(" "), boost::token_compress_on );

    return splitVec;
}

int getIndex(string raw_line)
{
	vector<string> splitVec = splitVector(raw_line);

    //gets time from string in hours:minutes:seconds format
    string time =  getTime(splitVec.at(3));

	//extract values for hours and minutes and convert to int to be used as indexes
    int hours   = getHours(time);
    int minutes = getMinutes(time);
    int seconds = getSeconds(time);

    int index = ((hours * 3600) + (minutes * 60) + seconds);

	return index;
}

string getName(string raw_line)
{
	vector<string> splitVec = splitVector(raw_line);

    //gets name from string 
    string name =  splitVec.at(2);

    return name;
}

string getIP(string raw_line)
{
	vector<string> splitVec = splitVector(raw_line);

    //gets name from string 
    string IP =  splitVec.at(0);

    return IP;
}