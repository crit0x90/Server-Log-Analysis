#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <chrono>
#include <unistd.h>
#include <utility>
#include <fstream>
#include <functional>
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

struct record {
	record(time_t ts, string name)
	{		
		data = name;
		pqueue_next = nullptr;
	}
	record* pqueue_next;
	time_t timestamp;
	string data;
};

*/
/*
//orders from closest -> furthest  timestamp
class P_Queue {
public:
	P_Queue();
	~P_Queue();
	void insert(pair<time_t, record*> p);
	record* get_front();
	void del();
	void display();
private:
	pair<time_t, record*>* front;
};

P_Queue::P_Queue()
{
	front = nullptr;
}

void P_Queue::insert(pair<time_t, record*> p)
{
	//timestamps further in the future are comparably greater
	//empty case

	if(front == nullptr)
	{
		front = p;
	}
	else if(front.first > p.first)
	{
		p.second->pqueue_next = front;
		front = p.second;
	}
	else
	{
		record* temp = front;
		while(p.second->timestamp > temp->timestamp)
		{
			if(temp->pqueue_next == nullptr)
			{
				temp->pqueue_next = p.second;
			}
			else if(temp->pqueue_next->timestamp >= p.second->timestamp)
			{
				p.second->pqueue_next = temp->pqueue_next;
				temp->pqueue_next = p.second;

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
*/

bool pair_greater(pair<time_t, record*> a, pair<time_t, record*> b)
{
	if(a.first > b.first)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	using chrono::system_clock;
	chrono::duration<int, ratio<60*60*24> > one_day (1);

	priority_queue<pair<time_t, record*>, vector<pair<time_t, record*> >,\
	 function<bool(pair<time_t, record*> , pair<time_t, record*>)> > queue(pair_greater);
	
	system_clock::time_point currentTime = system_clock::now();
	time_t tt = system_clock::to_time_t(currentTime);

    record* r = new record(tt, "bob");
    record* r2 = new record(tt+10, "joe"); 

    queue.push(make_pair(tt, r));
    queue.push(make_pair(tt+10, r));

    cout << queue.top().second->data << endl;
    queue.top().second->data = "larry";
    queue.pop();
    cout << queue.top().second->data << endl;
    /*
    while(queue.size() > 0)
    {
    	cout << queue.top().second->data << endl;
    	queue.pop();

    }
    */
	
	return 0;
}