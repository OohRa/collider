// Board representation

#include "primer.h"
#include "board.h"


int getPiece( int sq ){
	return board.sq[sq];
}	

int getColor( int sq ){
	int sqVal;
	sqVal = getPiece( sq );

	if( sqVal >= wqR && sqVal <= wPh ) return WHITE;
	else if( sqVal >= bqR && sqVal <= bPh ) return BLACK;
	else if( sqVal == 0 )
		return NONE;
	else return OFFBOARD;
}

int getType ( int sq ){
	int type, piece;
	
	piece = getPiece( sq );

	//Check what type the piece is.
	switch ( piece ){
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
		default: type = PAWN; break;
	}
	if( piece == 0 ) type = EMPTY;
	
	if( piece == -1 ) type = OFFBOARD;
	return type;
}

