#ifndef BOARD_H
#define BOARD_H
//board.h

//Takes a square and returns the piece value
inline int getPiece( const int sq ){
	return board.sq[sq];
}	

//Take a square and returns the color of the piece on that square
inline int getColor( const int sq ){
	int sqVal;
	sqVal = getPiece( sq );

	//Check for color
	if( sqVal >= wqR && sqVal <= wPh )      //White piece
		 return WHITE;
	else if( sqVal >= bqR && sqVal <= bPh ) //Black Pieces
		 return BLACK;
	else if( sqVal == EMPTY ) 		//Empty squares
		return NONE;
	else return OFFBOARD;			//General else
}

//Takes a square and returns type of piece on that square
inline int getType ( const int sq ){
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

	//Check for pawnQueens
	if( type == PAWN )
		if( pce[piece].type == QUEEN )
			type = QUEEN;	
	if( piece == EMPTY )
		 type = NOTYPE;
	
	if( piece == -1 )
		 type = OFFBOARD;

	return type;
}

inline int getValue( const int sq ){
	int val;

	switch(getType(sq)){
		case PAWN: val = PVAL; break;
		case KNIGHT: val = NVAL; break;
		case BISHOP: val = BVAL; break;
		case ROOK: val = RVAL; break;
		case QUEEN: val = QVAL; break;
		case KING: val = KVAL; break;
		default: val = NOVAL; 
	}
	
	return val;
}

inline void setMove( std::vector<int>& moveList, const int index ){
	board.frSq = moveList[index]/100;
	board.toSq = moveList[index]%100;
	if( board.frSq < 20 || board.frSq > 98 )
		std::cout << "frSq Error in setMove!: " << board.frSq << "\n";
	if( board.toSq < 20 || board.toSq > 98 )
		std::cout << "toSq Error in setMove!: " << board.toSq << "\n";
}

void dispMove( int move );
void dispSq( int sq );
int getOpp();
#endif
