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
#include "eval.h"
#include "search.h"

int life;

int main(){	
	/* Main game loop */
	initializeAll();
	while( !stop ){
		displayAll();
		engine();
		debugAll();
		displayAll();
		std::cout << "Test 1\n";
		userInput();
		std::cout << "Test 2\n";
		if( stop )
			 return 0;
		makeMove();
		changeSide();
	}
	closeSDL();
	return 0;

/*
	initializeAll();
	while( !stop ){
		displayAll();
		engine();
		//SDL_Delay(1000);
	}
	closeSDL();
	return 0;
*/		
/*
	initializeAll();
	for( int i = 1; i < 121; i++ ){
		if( board.sq[i-1] < 10 && board.sq[i-1] > 0 )
			std::cout << " ";
		std::cout << board.sq[i- 1] << " ";
		if( i % 10 == 0 )
			std::cout << "\n";
	}
*/
}



