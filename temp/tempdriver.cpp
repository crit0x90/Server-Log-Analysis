#include <iostream> 
#include <vector>
#include <chrono>
#include <unistd.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <queue>
#include "newheader.h"
/*
	TT IS COMPARABLE, OLDTIME IS < NEWTIME

	THIS IS HOW THE TIMING WILL WORK
	using std::chrono::system_clock;
	std::chrono::duration<int,std::ratio<60*60*24> > one_day (1);
	auto flood_length = chrono::duration<int, ratio<40> > (1);

	system_clock::time_point today = system_clock::now();

	std::time_t tt;

	tt = system_clock::to_time_t(today);
	std::cout << "Today is: " << ctime(&tt) << std::endl;
*/

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


time_t processLine(string name, string ip)
{
	system_clock::time_point today = system_clock::now();

	time_t tt;
	time_t tt2;

	tt = system_clock::to_time_t(today);
	//cout << "Today is: " << ctime(&tt) << endl;

	tt2 = system_clock::to_time_t(today+LOOKAHEAD_LENGTH);
	//cout << "Today is: " << ctime(&tt2) << endl;

	Userdata* user = new Userdata(name, ip);
	//user->floodExpirationTime = system_clock::to_time_t(today+FLOOD_LOOKAHEAD_LENGTH);

	return tt;
}

int main()
{
	string line = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:31 -0700]";
	string name = getName(line);
	string ip = getIP(line);

	using chrono::system_clock;
	chrono::duration<int, ratio<60*60*24> > one_day (1);
	
	readConfig();


	Userdata* user = new Userdata(name, ip);
	user->expirationTime = processLine(name, ip);

	queue<Userdata*> queue;
	queue.push(user);

	cout << ctime(&queue.front()->expirationTime) << endl; 

	return 0;
}