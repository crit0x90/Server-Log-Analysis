#include <iostream>
#include <string>
using namespace std;

//usage: ./drive | python ../utilities/printer.py

int main()
{
	string lineInput;
	while (getline(cin,lineInput)) 
	{
  		cout << lineInput;
	}
	return 0;
}