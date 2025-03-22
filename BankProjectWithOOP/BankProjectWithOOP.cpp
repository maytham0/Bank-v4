#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"
using namespace std;

//we need set a defult encrpyion key 
//our key is : 3610

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
	
	return 0;
}


