#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "header.h"

using namespace std;

map<string, int> monthMap;
map<int, string> reverseMonthMap;
map<int, int> daycountMap;
typedef long int TIME_TYPE;

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

void alertAdministrator(tuple<string, int, string, string, TIME_TYPE> t)
{
	ofstream outfile;
	outfile.open("report.txt", ios::app);

	outfile << "Alert recieved at time: " << toReadableTime(get<4>(t)) << endl;
	outfile << "Reason for alert: " << get<0>(t) << endl;
	outfile << "Alert recieved at line number: " << get<1>(t) << endl;
	outfile << "Username of triggering record: " << get<2>(t);
	outfile << "\tIP address of triggering record: " << get<3>(t) << endl;
	outfile << endl;

	outfile.close();
}

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

TIME_TYPE toTimeType(string raw_line)
{
	//initialization
	typedef vector<string> split_vector_type;
	//splits the string
	split_vector_type splitVec;
	std::string::size_type sz;
	boost::split( splitVec, raw_line, boost::is_any_of(" "), boost::token_compress_on );

	string datetime = splitVec.at(3);
	TIME_TYPE timestamp;

	string year = datetime.substr(10, 2);
	string month = datetime.substr(4, 3);
	string day = datetime.substr(1, 2);
	string hours = datetime.substr(13, 2);
	string minutes = datetime.substr(16, 2);
	string seconds = datetime.substr(19,2);

	/*
		cout << "Datetime: " << datetime << endl;
		cout << "Year: " << stoi(year, &sz) << endl;
		cout << "Month: " << month << endl;
		cout << "Day: " << stoi(day, &sz) << endl;
		cout << "Hours: " << stoi(hours, &sz) << endl;
		cout << "Minutes: " << stoi(minutes, &sz) << endl;
		cout << "Seconds: " << seconds << endl;
	*/
	timestamp = stoi(year, &sz) * 10000000000; //10,000,000,000
	timestamp = timestamp + (monthMap[month] * 100000000); // 100,000,000
	timestamp = timestamp + (stoi(day, &sz) * 1000000); //1,000,000
	timestamp = timestamp + (stoi(hours, &sz) * 10000); //10,000
	timestamp = timestamp + (stoi(minutes, &sz) * 100);
	timestamp = timestamp + (stoi(seconds, &sz));

	//FORM OF TIMESTAMP - commas are for readability
	//YYM,MDD,HHM,MSS
	return timestamp;
}

string toReadableTime(TIME_TYPE integerTime)
{
	if(integerTime == 0)
	{
		return "0";
	}
	else if (integerTime == -1)
	{
		return "-1";
	}
	else
	{
		string readableTime = "20";
		string intTime = to_string(integerTime);
		string year = readableTime.append(intTime.substr(0, 2)); //YYYY
		string month = reverseMonthMap[((integerTime % 10000000000) / 100000000)];
		string day = intTime.substr(4,2);
		string hours = intTime.substr(6,2);
		string mins = intTime.substr(8,2);
		string secs = intTime.substr(10,2);

		string date = month.append("/").append(day).append("/").append(year);// MM/DD/YYYY
		string time = hours.append(":").append(mins).append(":").append(secs);// HH:MM:SS
		readableTime = date.append(":").append(time);// MM/DD/YYYY:HH:MM:SS

		return readableTime;
	}
}

TIME_TYPE incrementTimeStamp(TIME_TYPE old_stamp, long int lookahead)
{
	//this function assumes that the lookahead is <= 86400 (1 day)
	int days = lookahead / 84600;
	//cout << "Days: " << days << endl;
	lookahead = lookahead % 84600;

	int hours = lookahead / 3600;
	//cout << "Hours: " << hours << endl; 
	lookahead = lookahead % 3600;

	int minutes = lookahead / 60;
	//cout << "Minutes: " << minutes << endl;
	lookahead = lookahead % 60;

	int seconds = lookahead;
	//cout << "Seconds: " << seconds << endl;

	if(lookahead > 86400 || lookahead < 0)
	{	
		cerr << "---Error recieved in incrementTimeStamp---" << endl;
		cerr << "Lookahead value has exceeded maximum limit. \t Value: " << lookahead << endl;
		exit(0);
	}
	else
	{
		old_stamp += (days * 1000000);
		old_stamp += (hours * 10000);
		old_stamp += (minutes * 100);
		old_stamp += seconds;

		//At this stage the time has the correct amounts added
		//but the form may be incorrect. i.e. there may be > 60
		//hours/minutes/seconds
		
		//cout << "Incremented derived time: " << old_stamp << endl;
		//cout << "Incremented time: " << toReadableTime(old_stamp) << endl;

		//fix seconds - done
		if(old_stamp % 100 > 59)
		{
			//cout << "Fixing seconds" << endl;
			int addMinutes = (old_stamp % 100) / 60;
			//cout << "Adding " << addMinutes << " minutes" << endl;
			old_stamp -= (60 * addMinutes);
			old_stamp += (100 * addMinutes);
		}

		//fix minutes - done
		if((old_stamp % 10000) / 100 > 59)
		{
			//cout << "Fixing minutes" << endl;
			int addHours = ((old_stamp % 10000) / 100) / 60;
			//cout << "Adding " << addHours << " hours" << endl;
			old_stamp -= (6000 * addHours);
			old_stamp += (10000 * addHours);
		}

		//fix hours - done
		if((old_stamp % 1000000) / 10000 > 23)
		{
			//cout << "Fixing hours" << endl;
			int addDays = ((old_stamp % 1000000) / 10000) / 24;

			old_stamp -= (240000 * addDays);
			old_stamp += (1000000 * addDays);
		}

		//fix days - done
		if((old_stamp % 100000000) / 1000000 > daycountMap[((old_stamp % 10000000000) / 100000000)])
		{
			//cout << "Fixing days" << endl;
			int addMonths = ((old_stamp % 100000000) / 1000000) / \
				daycountMap[((old_stamp % 10000000000) / 100000000)];
			
			old_stamp -= ((daycountMap[((old_stamp % 10000000000) / 100000000)] * 1000000) * addMonths);
			old_stamp += (100000000 * addMonths);
		}

		//fix months - done
		if((old_stamp % 10000000000) / 100000000 > 12)
		{
			//cout << "Fixing months" << endl;
			int addYears = ((old_stamp % 10000000000) / 100000000) / 13;
			
			old_stamp -= (1200000000);
			old_stamp += (10000000000 * addYears);
			cout << addYears << endl;
		}

		return old_stamp;
	}
	//add the computed values to the timestamp 
}

