#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

using namespace std;

map<string, int> monthMap;
map<int, string> reverseMonthMap;

void populateMonthMap()
{
	monthMap.insert(make_pair("Jan", 1));
	monthMap.insert(make_pair("Feb", 2));
	monthMap.insert(make_pair("Mar", 3));
	monthMap.insert(make_pair("Apr", 4));
	monthMap.insert(make_pair("May", 5));
	monthMap.insert(make_pair("Jun", 6));
	monthMap.insert(make_pair("Jul", 7));
	monthMap.insert(make_pair("Aug", 8));
	monthMap.insert(make_pair("Sep", 9));
	monthMap.insert(make_pair("Oct", 10));
	monthMap.insert(make_pair("Nov", 11));
	monthMap.insert(make_pair("Dec", 12));
}

void populateReverseMonthMap()
{
	reverseMonthMap.insert(make_pair(1, "Jan"));
	reverseMonthMap.insert(make_pair(2, "Feb"));
	reverseMonthMap.insert(make_pair(3, "Mar"));
	reverseMonthMap.insert(make_pair(4, "Apr"));
	reverseMonthMap.insert(make_pair(5, "May"));
	reverseMonthMap.insert(make_pair(6, "Jun"));
	reverseMonthMap.insert(make_pair(7, "Jul"));
	reverseMonthMap.insert(make_pair(8, "Aug"));
	reverseMonthMap.insert(make_pair(9, "Sep"));
	reverseMonthMap.insert(make_pair(10, "Oct"));
	reverseMonthMap.insert(make_pair(11, "Nov"));
	reverseMonthMap.insert(make_pair(12, "Dec"));
}

unsigned long long int toTimeType(string data)
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
	timestamp = timestamp + (monthMap[month] * 100000000); // 100,000,000
	timestamp = timestamp + (stoi(day, &sz) * 1000000); //1,000,000
	timestamp = timestamp + (stoi(hours, &sz) * 10000); //10,000
	timestamp = timestamp + (stoi(minutes, &sz) * 100);
	timestamp = timestamp + (stoi(seconds, &sz));
	return timestamp;
}

string toReadableTime(unsigned long long int integerTime)
{
	string readableTime = "20";
	string intTime = to_string(integerTime);
	string year = readableTime.append(intTime.substr(0, 2)); 
	string month = reverseMonthMap[((integerTime % 10000000000) / 100000000)];
	string day = intTime.substr(4,2);
	string hours = intTime.substr(6,2);
	string mins = intTime.substr(8,2);
	string secs = intTime.substr(10,2);

	string date = month.append("/").append(day).append("/").append(year);
	string time = hours.append(":").append(mins).append(":").append(secs);
	readableTime = date.append(":").append(time);

	return readableTime;
}

unsigned long long int incrementTimeStamp(TIME_TYPE old_stamp, long int lookahead)
{

}

int main()
{
	string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:38 -0700]";
	string readableTime;
	unsigned long long int TIME_TYPE;
	long int lookahead = 10;

	populateMonthMap();
	populateReverseMonthMap();

	TIME_TYPE = toTimeType(testLine);
	readableTime = toReadableTime(TIME_TYPE);

	cout << "Derived time: " << TIME_TYPE << endl;
	cout << "Readable time: " << readableTime << endl;

	incrementTimeStamp(TIME_TYPE, lookahead);
	cout << "Lookahead distance: " << lookahead << endl;

	return 0;
}
