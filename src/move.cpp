//move.cpp

#include "primer.h"
#include "move.h"


void makeMove(boardStruct &board, pieceStruct pieces[], bool &stop){

	int piece, toVal;

	if( stop )
		return;	

	/* Makes the users move */
	piece = board.sq120[board.frSq];
	toVal = board.sq120[board.toSq];
	board.oldPiece = piece;
	board.oldVal = toVal;
	board.sq120[board.frSq] = EMPTY;
	board.sq120[board.toSq] = piece;

	/* Update piecelist */
	pieces[piece].position = board.toSq;
	pieces[toVal].position = DEAD;

	//Switches board.sides
	if( board.side == WHITE )
		board.side = BLACK;
	else board.side = WHITE;	


}

void unmakeMove( boardStruct &board, pieceStruct pieces[], bool &stop){

	int piece, toVal;
	
	if( stop )
		return;

	/* Unmakes the users move */
	board.sq120[board.toSq] = board.oldVal;
	board.sq120[board.frSq] = board.oldPiece;

	pieces[board.oldVal].position = board.toSq;
	pieces[board.oldPiece].position = board.frSq;
