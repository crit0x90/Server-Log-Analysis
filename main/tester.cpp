#include <iostream> 
#include <vector>
#include <string>
#include "header.h"

using namespace std;

int main()
{
	string line = "IP7379 [yfsOU0T2XLuEfWr] user1624 [04/Sep/2017:00:01:22 -0700]";

	time_t t = getTimestamp(line);

	return 0;
}