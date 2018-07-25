#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

using namespace std;

map<string, int> monthMap;
map<int, string> reverseMonthMap;
map<int, int> daycountMap;
typedef unsigned long long int TIME_TYPE;

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

void populateDaycountMap()
{
	daycountMap.insert(make_pair(1, 31));
	daycountMap.insert(make_pair(2, 28));
	daycountMap.insert(make_pair(3, 31));
	daycountMap.insert(make_pair(4, 30));
	daycountMap.insert(make_pair(5, 31));
	daycountMap.insert(make_pair(6, 30));
	daycountMap.insert(make_pair(7, 31));
	daycountMap.insert(make_pair(8, 31));
	daycountMap.insert(make_pair(9, 30));
	daycountMap.insert(make_pair(10, 31));
	daycountMap.insert(make_pair(11, 30));
	daycountMap.insert(make_pair(12, 31));
}

TIME_TYPE toTimeType(string data)
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

string toReadableTime(TIME_TYPE integerTime)
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

//if anyone ever has to debug this I am sorry for this mess, I owe you a beer
//this function basically fixes any illegalities in the time formatting
//(i.e. > 59 seconds in the seconds field)
TIME_TYPE incrementTimeStamp(TIME_TYPE old_stamp, long int lookahead)
{
	int days = lookahead / 84600;
	cout << "Days: " << days << endl;
	lookahead = lookahead % 84600;

	int hours = lookahead / 3600;
	cout << "Hours: " << hours << endl; 
	lookahead = lookahead % 3600;

	int minutes = lookahead / 60;
	cout << "Minutes: " << minutes << endl;
	lookahead = lookahead % 60;

	int seconds = lookahead;
	cout << "Seconds: " << seconds << endl;

	old_stamp += (days * 1000000);
	old_stamp += (hours * 10000);
	old_stamp += (minutes * 100);
	old_stamp += seconds;

	//At this stage the time has the correct amounts added
	//but the form may be incorrect. i.e. there may be > 60
	//hours/minutes/seconds
	
	cout << "Incremented derived time: " << old_stamp << endl;
	cout << "Incremented time: " << toReadableTime(old_stamp) << endl;

	//fix seconds - done
	if(old_stamp % 100 > 59)
	{
		cout << "Fixing seconds" << endl;
		int addMinutes = (old_stamp % 100) / 60;
		//cout << "Adding " << addMinutes << " minutes" << endl;
		old_stamp -= (60 * addMinutes);
		old_stamp += (100 * addMinutes);
	}

	//fix minutes - done
	if((old_stamp % 10000) / 100 > 59)
	{
		cout << "Fixing minutes" << endl;
		int addHours = ((old_stamp % 10000) / 100) / 60;
		//cout << "Adding " << addHours << " hours" << endl;
		old_stamp -= (6000 * addHours);
		old_stamp += (10000 * addHours);
	}

	//fix hours - done
	if((old_stamp % 1000000) / 10000 > 23)
	{
		cout << "Fixing hours" << endl;
		int addDays = ((old_stamp % 1000000) / 10000) / 24;

		old_stamp -= (240000 * addDays);
		old_stamp += (1000000 * addDays);
	}

	//fix days - done
	if((old_stamp % 100000000) / 1000000 > daycountMap[((old_stamp % 10000000000) / 100000000)])
	{
		cout << "Fixing days" << endl;
		int addMonths = ((old_stamp % 100000000) / 1000000) / \
			daycountMap[((old_stamp % 10000000000) / 100000000)];
		
		old_stamp -= ((daycountMap[((old_stamp % 10000000000) / 100000000)] * 1000000) * addMonths);
		old_stamp += (100000000 * addMonths);
	}

	//fix months - 
	if((old_stamp % 10000000000) / 100000000 > 12)
	{
		cout << "Fixing months" << endl;
		int addYears = ((old_stamp % 10000000000) / 100000000) / 13;
		
		old_stamp -= (1200000000);
		old_stamp += (10000000000 * addYears);
		cout << addYears << endl;
	}

	return old_stamp;
}

int main()
{
	string testLine = "IP7379 [yfsOU0T2XLuEfWr] user1624 [31/Dec/2017:23:59:50 -0700]";
	string readableTime;
	TIME_TYPE CURRENT_STAMP;
	long int lookahead = 10;

	populateMonthMap();
	populateReverseMonthMap();
	populateDaycountMap();

	CURRENT_STAMP = toTimeType(testLine);
	readableTime = toReadableTime(CURRENT_STAMP);

	cout << endl << "Derived time: " << CURRENT_STAMP << endl;
	cout << "Readable time: " << readableTime << endl;

	cout << "Lookahead distance: " << lookahead << endl;
	CURRENT_STAMP = incrementTimeStamp(CURRENT_STAMP, lookahead);

	cout << endl << "Adjusted incremented derived time: " << CURRENT_STAMP << endl;
	cout << "Adjusted incremented time: " << toReadableTime(CURRENT_STAMP) << endl;

	return 0;
}
