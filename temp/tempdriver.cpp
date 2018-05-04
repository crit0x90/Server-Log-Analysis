#include <iostream> 
#include <vector>
#include <chrono>
#include <unistd.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <queue>
#include <string>
#include <map>
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


int main()
{
	map<string, map<string, int> > testMap;

	testMap["a"]["aa"] = 1;
	testMap["b"]["bb"] = 2;
	testMap["a"]["bb"] = 3;

	cout << "Size: " << testMap.size() << endl;
	cout << "Size: " << testMap["a"].size() << endl;
	cout << "Size: " << testMap["b"].size() << endl;

	return 0;
}