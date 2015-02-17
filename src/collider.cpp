//collider.cpp

#include <iostream>
#include "primer.h"
#include "collider.h"
#include "display.h"
#include "initial.h"
#include "input.h"
#include "legal.h"
#include "move.h"
#include "debug.h"
#include "board.h"

int life;

int main(){	

	life = 0;

	/* Main game loop */

	initializeAll();
	displayAll();
	while( !stop ){
		userInput();
		if( stop ) return 0;
		makeMove();
		changeSide();
		displayAll();	
	}






/* Old Game Loop */
/*
	initializeAll();
	displayAll();
	while( !stop ){
		while( userEntry(); ){
			userEntry();
			if( stop ) return 0;
			while( !checkLegal() ){
				displayAll();
				userEntry();
				life++;
				if( stop ) return 0;
			}
			while( checkCheck() ){
				displayAll();
				userEntry();
				life++;
				if( stop ) return 0;
				while( !checkLegal() ){
					displayAll();
					userEntry();
					life++;
					if( stop ) return 0;
				}
			}
		}
		makeMove();
		(board.side == WHITE) ? board.side = BLACK : board.side = WHITE;
		displayAll();
	}	
*/
	//Debugging
/*
	initializeAll( board, pieces, indexArray, bb );
	debugAll( board, pieces );
*/
}



