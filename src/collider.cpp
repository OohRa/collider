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
#include "sdl.h"

int life;

int main(){	

	/* Main game loop */
	initializeAll();
	//Debug
//	debugAll();

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
	initializeAll();
	debugAll();
*/

	closeSDL();
	return 0;
}



