//collider.cpp
/*************************************************************
 * Collider Chess Engine
 * Version: 0.5
 * By: Dylan James Kolb-Bond
 * Currently Done: Board Representation and SDL Graphics
 * Need to be completed: Move generation, search and evaluate
 * Known bugs: Cannot undo multiple times
 *************************************************************/
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
	debugAll();
	displayAll();
	while( !stop ){
		userInput();
		if( stop )
			 return 0;
		makeMove();
		changeSide();
		displayAll();	
	}
	closeSDL();
	return 0;
}



