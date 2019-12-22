#include "System.h"
#include <iostream>
using namespace std;

#pragma warning(disable:4996) 

// We should move all this to Menu File 

int main()
{
	System system("eBen"); // Our defult system name
	system.interactiveMenu();

	return 0;
}