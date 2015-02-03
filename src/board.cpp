// Board representation

#include "primer.h"
#include "board.h"

int checkColor( int sqVal ){
	if( sqVal >= wqR && sqVal <= wPh ) return WHITE;
	else if( sqVal >= bqR && sqVal <= bPh ) return BLACK;
	else	return NONE;
}

int checkType ( int piece ){
	int type;
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
	return type;
}
