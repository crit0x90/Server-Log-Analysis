#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
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

void freeNode(Userdata* node)
{
	node->username  = "NULLPTR";
	node->IPaddress = "NULLPTR";
	node->floodStamp = 0;
	node->userStamp = 0;
	node->ipStamp = 0;
}

void alertAdministrator(tuple<string, int, string, string, time_t> t)
{
	ofstream outfile;
	outfile.open("report.txt", ios::app);

	outfile << "Alert recieved at time: " << get<4>(t) << endl;
	outfile << "Reason for alert: " << get<0>(t) << endl;
	outfile << "Alert recieved at line number: " << get<1>(t) << endl;
	outfile << "Username of triggering record: " << get<2>(t) << endl;
	outfile << "IP address of triggering record" << get<3>(t) << endl;
	outfile << endl;

	outfile.close();
}