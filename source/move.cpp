//move.cpp

#include "primer.h"
#include "move.h"


void makeMove(boardStruct &board, bool &stop)
{

	if( stop )
		return;	

	/* Makes the users move */
	int piece;
	piece = board.sq120[board.frSq];
	board.sq120[board.frSq] = EMPTY;
	board.sq120[board.toSq] = piece;
	//Switches board.sides
	if( board.side == WHITE )
		board.side = BLACK;
	else board.side = WHITE;	


}
