#include "System.h"
#include <iostream>
using namespace std;




int main()
{
	
	ifstream inFile("users.txt", ios::_Nocreate); 

	if (inFile.is_open())  
	{
		System system("users.txt", "eBen"); // Our default system name
		system.interactiveMenu();
	}
	else  
	{
		System system("eBen");
		system.interactiveMenu();
	}

	return 0;
}