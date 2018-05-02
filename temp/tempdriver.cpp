#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <chrono>
#include <unistd.h>
#include <utility>
#include <fstream>
#include <set>

using namespace std;
using chrono::system_clock;
//#include "newheader.h"
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

/*
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

//returns expiration time
time_t processLine(string name, string ip)
{
	system_clock::time_point today = system_clock::now();

	time_t tt;
	
	tt = system_clock::to_time_t(today);
	//cout << "Today is: " << ctime(&tt) << endl;
	//tt += 30;
	//cout << "Today is: " << ctime(&tt) << endl;

	Userdata* user = new Userdata(name, ip);
	//user->floodExpirationTime = system_clock::to_time_t(today);

	return tt;
}

*/

struct record {
	record(time_t ts, string name)
	{		
		timestamp = ts;
		data = name;
		pqueue_next = nullptr;
	}
	record* pqueue_next;
	time_t timestamp;
	string data;
};

//orders from closest -> furthest  timestamp
class P_Queue {
public:
	P_Queue();
	~P_Queue();
	void insert(record* item);
	record* get_front();
	void del();
	void display();
private:
	record* front;
};

P_Queue::P_Queue()
{
	front = nullptr;
}

void P_Queue::insert(record* item)
{
	//timestamps further in the future are comparably greater
	//empty case
	if(front == nullptr)
	{
		front = item;
	}
	else if(front->timestamp > item->timestamp)
	{
		item->pqueue_next = front;
		front = item;
	}
	else
	{
		record* temp = front;
		while(item->timestamp > temp->timestamp)
		{
			if(temp->pqueue_next == nullptr)
			{
				temp->pqueue_next = item;
			}
			else if(temp->pqueue_next->timestamp >= item->timestamp)
			{
				item->pqueue_next = temp->pqueue_next;
				temp->pqueue_next = item;
			}

			temp = temp->pqueue_next;
		}
	}
}

record* P_Queue::get_front()
{
	return front;
}

void P_Queue::del()
{
	record* temp = front;
	front = temp->pqueue_next;
	delete temp;
}

void P_Queue::display()
{
	record* temp = front;
	if(temp == nullptr)
	{
		cout << "Priority queue is empty" << endl;
	}
	else if(temp->pqueue_next == nullptr)
	{
		cout << "(" << temp->data << ", " << temp->timestamp << ")" << endl;
	}
	else
	{
		while(temp->pqueue_next != nullptr)
		{
			cout << "(" << temp->data << ", " << temp->timestamp << ")" << endl;
		}
		cout << "(" << temp->data << ", " << temp->timestamp << ")" << endl;
	}
}


int main()
{
/*
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

	//cout << ctime(&queue.front()->expirationTime) << endl; 
*/
	P_Queue* queue = new P_Queue();

	system_clock::time_point currentTime = system_clock::now();
	time_t tt = system_clock::to_time_t(currentTime);

    record* r = new record(tt, "bob");
    record* r2 = new record(tt+10, "joe"); 

    queue->insert(r);
    queue->insert(r2);

    queue->display();

	return 0;
}