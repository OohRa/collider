//Main

#include "primer.h"
#include "stdio.h"
#include "stdlib.h"

int main()
{
	/* Main game loop */

	initializeAll();
	while( !stop )
	{
		displayAll();
		userEntry();
		while((!checkLegal() && !stop))
		{
			displayAll();
			userEntry();
		}
		makeMove();
		checkCheck();
	}



/*
	//Debugging
	initializeAll();
	bitboardDebug();
*/
}



