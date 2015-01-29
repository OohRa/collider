//collider.cpp

#include "primer.h"
#include "collider.h"
#include "display.h"
#include "initial.h"
#include "input.h"
#include "legal.h"
#include "move.h"
#include "debug.h"

int main()
{
	
	/* Main game loop */

	initializeAll(board, pieces, indexArray, bb);
	displayAll(board);
	while( !stop ){
		userInput(board, pieces, stop);
	}	
	



	//Debugging
/*
	initializeAll( board, pieces, indexArray, bb );
	boardDebug( board, pieces );
*/
}



