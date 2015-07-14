//collider.cpp
/*************************************************************
 * Collider Chess Engine
 * Version: 0.75
 * By: Dylan James Kolb-Bond
 * Currently Done: Board Representation, SDL Graphics, move generation
 * search, evaluate, quiescence search added. Improving evaluation. Need more expedient
 * search methods as the current search is terribly slow.
 * Need to be completed: Bitboards.
 * Known bugs: If being checkmated will sacrifice king
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

double life;

int main(){	
	int score = 0, signs[3] = {0,1,-1};

	/* Main game loop */
	initializeAll();
	bitboardDebug();
	while( !stop ){
		displayAll();
		if( thinkFlag )
			engine();
		moveGen( board.mL );
		//debugAll();
		displayAll();
		userInput();
		if( stop )
			 return 0;
		makeMove();
		bitboardDebug();
		score = signs[board.side] * eval();
		//debugAll();
		std::cout << "Score is " << score << "\n";
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



