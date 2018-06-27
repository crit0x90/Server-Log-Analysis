#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>


using namespace std;

long unsigned int toTimeType(string data)
{
	//initialization
	typedef vector<string> split_vector_type;
	//splits the string
	split_vector_type splitVec;
	std::string::size_type sz;
	boost::split( splitVec, data, boost::is_any_of(" "), boost::token_compress_on );

	string datetime = splitVec.at(3);
	unsigned long long int timestamp;
	string year = datetime.substr(10, 2);
	string month = datetime.substr(4, 3);
	string day = datetime.substr(1, 2);
	string hours = datetime.substr(13, 2);
	string minutes = datetime.substr(16, 2);
	string seconds = datetime.substr(19,2);

	cout << "Datetime: " << datetime << endl;
	cout << "Year: " << stoi(year, &sz) << endl;
	cout << "Month: " << month << endl;
	cout << "Day: " << stoi(day, &sz) << endl;
	cout << "Hours: " << stoi(hours, &sz) << endl;
	cout << "Minutes: " << stoi(minutes, &sz) << endl;
	cout << "Seconds: " << seconds << endl;
	
	timestamp = stoi(year, &sz) * 10000000000; //10,000,000,000

	timestamp = timestamp + (stoi(day, &sz) * )
	return timestamp;
}

int main()
{
	string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:38 -0700]";
	unsigned long long int TIME_TYPE;

	TIME_TYPE = toTimeType(testLine);

	cout << "Derived time: " << TIME_TYPE << endl;

	return 0;
}
