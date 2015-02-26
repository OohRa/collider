// Board representation

#include "primer.h"
#include "board.h"

//Takes a square and returns the piece value
int getPiece( int sq ){
	return board.sq[sq];
}	

//Take a square and returns the color of the piece on that square
int getColor( int sq ){
	int sqVal;
	sqVal = getPiece( sq );

	//Check for color
	if( sqVal >= wqR && sqVal <= wPh )      //White pieces
		 return WHITE;
	else if( sqVal >= bqR && sqVal <= bPh ) //Black Pieces
		 return BLACK;
	else if( sqVal == EMPTY ) 		//Empty squares
		return NONE;
	else return OFFBOARD;			//General else
}

//Takes a square and returns type of piece on that square
int getType ( int sq ){
	int type, piece;
	piece = getPiece( sq );

	//Check what type the piece is.
	switch ( piece ){		//Switch from display function
		case wqR:
		case wkR:
		case bqR:
		case bkR: type = ROOK; break;
		case wqN:
		case wkN:
		case bqN:
		case bkN: type = KNIGHT; break;
		case wqB:
		case wkB:
		case bqB:
		case bkB: type = BISHOP; break;
		case  wQ: 
		case  bQ: type = QUEEN; break;
		case  wK:
		case  bK: type = KING; break;
		default:  type = PAWN; break;
	}
	
	/* Check afterwards for empty and offboard squares
	   to use default option in switch for pawns */
	if( piece == EMPTY )
		 type = NOTYPE;
	
	if( piece == -1 )
		 type = OFFBOARD;

	return type;
}

