/*
 *	Collider 0.01 Chess Engine
 *	legal.cpp	
 *  Holds all functions involved in checking legality of moves.
 *
 *
 */
/////////////
#include <iostream>
#include "primer.h"
#include "legal.h"
#include "board.h"
#include "move.h" 

/* Check if the user or cpu move is legal */
bool checkLegal(boardStruct &board, pieceStruct pieces[], bool &stop){
	int piece, toColor, toValue;
	piece = board.sq120[board.frSq];
	toValue = board.sq120[board.toSq];
	toColor = checkColor( toValue );	

	//Exits out of the game loop.
	if( stop )
		return false;

	// Error check for invalid moves
	if( board.side != pieces[piece].color ){
		std::cout << "Invalid move. ";
		( board.side == WHITE ) ? std::cout << "White " : std::cout << "Black ";
		std::cout << "to move.\n";
		return false;
	}

	if( piece == NONE ){
		std::cout << "Invalid move. Empty square.\n";
		return false;
	}
	
	if( toColor == board.side ){
		std::cout << "Invalid move. Don't take your own piece.\n";
		return false;
	}

	/* 	Valid move checks	*/
	/* 	Knight valid check (NVC) */ 
	if( pieces[piece].type == KNIGHT ){
		int knightLegal[8];
		knightLegal[0] = (board.frSq - 21);
		knightLegal[1] = (board.frSq - 19);
		knightLegal[2] = (board.frSq - 12);
		knightLegal[3] = (board.frSq -  8);
		knightLegal[4] = (board.frSq +  8);
		knightLegal[5] = (board.frSq + 12);
		knightLegal[6] = (board.frSq + 19);
		knightLegal[7] = (board.frSq + 21);

		for( int index = 0; index < 8; index++ ){
			if( knightLegal[index] == board.toSq )
				return true;
		}
		
		std::cout << "Invalid move. Knights don't move like that.\n";
		return false;
	}

	/* Rook Valid Check (RVC) */
	if( pieces[piece].type == ROOK ){
		int indexSq, checkSq, diff, absDiff, slide;
		diff = ( (board.toSq - board.frSq) % 10 );
		absDiff = abs(board.toSq - board.frSq);
	
		if( diff != 0 && (absDiff > 7) ){		//Eliminates impossible rook moves
			std::cout << "Invalid move. Rooks don't move like that.\n";
			return false;
		}
		if( diff == 0 )					//Defines which way rook is sliding
			( board.toSq > board.frSq ) ? slide = 10 : slide = -10;
		else ( board.toSq > board.frSq ) ? slide = 1 : slide = -1;	

		//Check the direction the rook is moving
		for( indexSq = (board.frSq + slide); indexSq != board.toSq; indexSq += slide ){
			checkSq = board.sq120[indexSq];
			toColor = checkColor(checkSq);
			if( checkSq == board.toSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. Rooks can't move through pieces.\n";
				return false;
			}
			if( checkSq == -1 ){
				std::cout << "Invalid move. Offboard square.\n";
				return false;
			}
		}
	}

	/* Bishop Valid Check (BVC) */
	if( pieces[piece].type == BISHOP )
	{
		int indexSq, checkSq, diff, absDiff, slide;
		diff = (board.toSq - board.frSq);
		absDiff = abs(board.toSq - board.frSq);
		
		/* Negate any move that isn't a diagonal */
		if(!((absDiff % 11 == 0) || (absDiff % 9 == 0))){
			std::cout << "Invalid move. Bishop ain't move like that.\n";
			return false;
		}

		/* Define the movement */
		if(absDiff % 11 == 0) 
			(diff > 0) ? slide = 11: slide = -11;
		else if(absDiff % 9 == 0)
			(diff > 0) ? slide = 9: slide = -9;
		else return false;

		/* Check the direction the Bishop is moving */
		for( indexSq = (board.frSq + slide); indexSq != board.toSq; indexSq += slide ){
			checkSq = board.sq120[indexSq];
			toColor = checkColor(checkSq);
			if( checkSq == board.toSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. Bishops can't move through pieces.\n";
				return false;
			}
			if( checkSq == -1 ){
				std::cout << "Invalid move. Offboard Square.\n";
				return false;
			}
		}
	}

	/* Queen Valid Check (QVC) */	
	if( pieces[piece].type == QUEEN )
	{
		int indexSq, checkSq, diff, absDiff, slide;
		diff = (board.toSq - board.frSq);
		absDiff = (abs(board.toSq - board.frSq));
	
		/* Negate any move that isn't an option */
		if(!((absDiff % 11 == 0) || (absDiff % 9 == 0) || (absDiff % 10 == 0) || (absDiff < 7))){
			std::cout << "Invalid move. Queen can't be moving like that.\n";
			return false;
		}
		
		/* Define the movement */
		if( absDiff % 11 == 0)
			(diff > 0) ? slide = 11: slide = -11;
		else if( absDiff % 10 == 0)
			(diff > 0) ? slide = 10: slide = -10;
		else if( absDiff % 9 == 0)
			(diff > 0) ? slide = 9: slide = -9;
		else
			(diff > 0) ? slide = 1: slide = -1;

		/* Check the direction of movement */
		for( indexSq = (board.frSq + slide); indexSq != board.toSq; indexSq += slide ){
			checkSq = board.sq120[indexSq];
			toColor = checkColor(checkSq);
			if( checkSq == board.toSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. Queen can't move through pieces.\n";
				return false;
			}
			if( checkSq == -1 ){
				std::cout << "Invalid move. Offboard Square.\n";
				return false;
			}
		}
	
	}

	/* King Check Valid (KCV) */
	if( pieces[piece].type == KING ){
		int indexSq, checkSq, diff, absDiff, slide;
		diff = (board.toSq - board.frSq);
		absDiff = abs(diff);

		/* Negate any moves outside range */
		if( absDiff > 11 ){
			std::cout << "Invalid move. Outside King's range.\n";
			return false;
		}
		
		/* Define the movement */
		if( absDiff % 11 == 0)
			(diff > 0) ? slide = 11: slide = -11;
		else if( absDiff % 10 == 0)
			(diff > 0) ? slide = 10: slide = -10;
		else if( absDiff % 9 == 0)
			(diff > 0) ? slide = 9: slide = -9;
		else
			(diff > 0) ? slide = 1: slide = -1;

		/* Check the direction of movement */
		for( indexSq = (board.frSq + slide); indexSq != board.toSq; indexSq += slide ){
			checkSq = board.sq120[indexSq];
			toColor = checkColor(checkSq);
			if( checkSq == board.toSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. King can't move through pieces.\n";
				return false;
			}
			if( checkSq == -1 ){
				std::cout << "Invalid move. Offboard Square.\n";
				return false;
			}
		}
	}
	
	/* Pawn Valid Check (PVC) */		
	if( pieces[piece].type == PAWN ){
		int checkSq, diff, absDiff, piece, toValue, toColor, slide;
		piece = board.sq120[board.frSq];
		toValue = board.sq120[board.toSq];
		toColor = checkColor(toValue);
		diff = board.toSq - board.frSq;;
		absDiff = abs(diff);

		/* Negate non-legal pawn moves */
		if(!((absDiff % 10 == 0) || (absDiff % 11 == 0) || (absDiff % 9 == 0) || (absDiff % 20 == 0) )){
			std::cout << "Invalid move. Pawns can't be moving that ways.\n";
			return false;
		}
		if( absDiff > 11 && absDiff != 20 ){
			std::cout << "Invalid move. Pawns can't be flying 'round.\n";
			return false;
		}
		
		/* Simple check if pawns are trying to move backwards */
		if( (diff < 0) && board.side == WHITE ){
			std::cout << "Pawns can't move backwards.\n";
			return false;	
		}
		if( (diff > 0) && board.side == BLACK ){
			std::cout << "Pawns can't move backwards.\n";
			return false;
		}
		
		/* Negates OFFBOARD squares */
		if( board.toSq == -1 ){
			std::cout << "Invalid move. Can't move offboard.\n";
			return false;
		}
		
		/* Forward capture check */
		if( absDiff == 10 ){
			if( toColor != EMPTY ){
				std::cout << "Invalid move. Pawn can't capture forwards.\n";
				return false;
			}
			else return true;
		}

		/* Legal capture */
		if( ( absDiff == 9 || absDiff == 11 )){
			if( toColor != board.side && toColor != EMPTY ) return true;
			else if( toColor == EMPTY ){
				std::cout << "Invalid move. Pawns must capture diagonally.\n";
				return false;
			}			
		} 
		
		/* Legalizes two squares on first pawn move */
		if( absDiff == 20 ){
			if( toColor != EMPTY ){
				std::cout << "Invalid move. Pawns can't capture forwards.\n";
				return false;
			} 
			if( board.side == WHITE && board.frSq > H2 ){
				std::cout << "Invalid move. Pawns can only move two squares on their first move.\n";
				return false;
			}
			else if( board.side == BLACK && board.frSq < A7 ){
				std::cout << "Invalid move. Pawns can only move two squares on their first move.\n";
				return false;
			} 
			( board.side == WHITE ) ? slide = 10: slide = -10;
			for( checkSq = (board.frSq + slide); checkSq != board.toSq; checkSq += slide ){
				toValue = board.sq120[checkSq];
				if( toValue != EMPTY ){
					std::cout << "Invalid move. Piece be in the way.\n";
					return false;
				}
				if( checkSq == board.toSq ) return true;
			}
		}
	}


		
	return true;

}
/*  checkCheck function
 *  checks if the users move put his own king in check
 *  not if he put the opponents king in check.
 *  Search code (FCC)					 */
bool checkCheck(boardStruct &board, pieceStruct pieces[]){
	
	int kingSq, slide, index, toColor, toType, checkSq;

	int knightLegal[8] = { 21, 12, -8, -19, -21, -12, 8, 19 };	
	int moveDir[9] = { UP, UPRT, RT, DWNRT, DWN, DWNLEFT, LEFT, UPLEFT, BREAK };

	makeMove( board, pieces );

	(board.side == WHITE) ? kingSq = pieces[wK].pos: kingSq = pieces[bK].pos;
	
	index = 0;
	/* Check the direction of movement */
	for( slide = moveDir[index]; slide != BREAK; index++ ){
		checkSq = 0;
		slide = moveDir[index];
		if( slide == BREAK ) break;
		for( int indexSq = (kingSq + slide); checkSq != OFFBOARD; indexSq += slide ){ 
			checkSq = board.sq120[indexSq];
			toColor = checkColor( checkSq );
			toType = checkType ( checkSq );
				
			if( checkSq == OFFBOARD ){
				break;
			}

			else if( toColor == board.side ){	
				break;
			}
			
			else if( toColor != board.side ){
				
				if( (abs(indexSq - kingSq) == 9 || abs(indexSq - kingSq) == 11) && toType == PAWN ){
					if( board.side == WHITE ){
						if( (indexSq - kingSq) > 0 ){
							std::cout << "Invalid move. You are in check by pawn.\n";
							unmakeMove( board, pieces );
							return true;
						}
					}
					else if( board.side == BLACK ){
						if( (indexSq - kingSq) < 0 ){
							std::cout << "Invalid move. You are in check by pawn\n Black to move";
							unmakeMove( board, pieces );
							return true;
						}
					}
				}
				if( toType == BISHOP || toType == QUEEN ){
					if( abs(slide) % 9 == 0 || abs(slide) % 11 == 0 ){
						std::cout << "Invalid move. You are in check by bishop or queen.\n";
						unmakeMove( board, pieces );
						return true;
					}
				}
				if( toType == ROOK || toType == QUEEN ){
					if( abs(slide) % 10 == 0 || slide == RT || slide == LEFT ){
						std::cout << "Invalid move. You are in check by rook or queen\n";
						unmakeMove( board, pieces );
						return true;
					}
				}
			}
		}
	}
					
	for( int index = 0; index < 8; index++ ){
		int checkSq = (board.sq120[kingSq + knightLegal[index]]);
		int toColor, toType;

		toColor = checkColor( checkSq );
		toType = checkType( checkSq );

		if( (toColor != board.side) && (toType == KNIGHT) ){
			std::cout << "Invalid move. That knight put you in check!\n"; 
			unmakeMove( board, pieces );
			return true;
		}
	}
	unmakeMove( board, pieces );
	return false;	

}
	



