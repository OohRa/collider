//move.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "board.h"

void makeMove(){

	int piece, toVal;
	
	
	/* Makes the users move */
	if( board.castling ){
		std::cout << "Test from makeMove castling.\n";
		int king, rook, diff, rookFrom, rookTo, kingTo; 
		diff = (board.oldtoSq - board.oldfrSq);
		king = board.sq[board.oldfrSq];
		if( diff > 0){
			 rookFrom = board.oldfrSq + 3;
			 rookTo = board.oldfrSq + 1;
			 kingTo = board.oldfrSq + 2;
		}
		else{
			rookFrom = board.oldfrSq - 4;
			rookTo = board.oldfrSq - 1;
			kingTo = board.oldtoSq - 1;
		}
		rook = board.sq[rookFrom];
		board.oldPiece = king;
		board.oldVal = rook;
		board.sq[board.oldfrSq] = EMPTY;
		board.sq[kingTo] = king;
		board.sq[rookFrom] = EMPTY;
		board.sq[rookTo] = rook;
		piece = board.sq[board.frSq];
		pieces[piece].pos = kingTo;
		pieces[rook].pos = rookTo;
		pieces[piece].moved++;
		pieces[rook].moved++;
		life++;
		
	}	
	
	else{
		int diff;
		diff = board.oldtoSq - board.oldfrSq;
		piece = board.sq[board.frSq];
		toVal = board.sq[board.toSq];
		board.oldPiece = piece;
		board.oldVal = toVal;
		board.sq[board.frSq] = EMPTY;
		board.sq[board.toSq] = piece;
		//Quick cover for promotions
		if( getType(board.toSq) == PAWN && (board.toSq > 91 || board.toSq < 31) ){
			board.sq[board.toSq] = (board.side = WHITE) ? wQ : bQ;
		} 

		//Remove the capture enPassant pawn
		if( board.enPas == board.toSq && getType(board.toSq) == PAWN){
			int enPiece;
			if( diff > 0 ){
				enPiece = board.sq[board.toSq - 10];
				board.sq[board.toSq - 10] = EMPTY;
				pieces[enPiece].pos = DEAD;
			}
			else {
				enPiece = board.sq[board.toSq + 10];
				board.sq[board.toSq + 10] = EMPTY;
				pieces[enPiece].pos = DEAD;
			}
		}

		/* Update piecelist */
		pieces[piece].pos = board.toSq;
		pieces[piece].moved++;
		life++;
	}

	
	//Create an enpassant square for the future
	if( getType(board.toSq) == PAWN && abs(board.oldtoSq - board.oldfrSq) == 20 ){
		int diff = board.oldtoSq - board.oldfrSq;	
		if(diff > 0) board.enPas = board.oldtoSq - 10;
		else board.enPas = board.oldtoSq + 10;
		//Debug
		std::cout << "Test from enpassant creation: " << board.enPas << "\n";
	}
	else board.enPas = 0;


}


void unmakeMove(){

	if( !board.castling ){

	/* Unmakes the users move */
	board.sq[board.toSq] = board.oldVal;
	board.sq[board.frSq] = board.oldPiece;

	pieces[board.oldVal].pos = board.toSq;
	pieces[board.oldPiece].pos = board.frSq;
	pieces[board.oldPiece].moved--;
	}
	
		
}

void changeSide(){	
	(board.side == WHITE) ? board.side = BLACK : board.side = WHITE;
}
