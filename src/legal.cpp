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
#include "debug.h"

/* Check if the user or cpu move is legal */
/* BCL */
bool checkLegal(){
	int piece, toColor, toValue;
	piece = board.sq[board.newfrSq];
	toValue = board.sq[board.newtoSq];
	toColor = getColor(board.newtoSq);	

	//Exits out of the game loop.
	if( stop )
		return false;

	// Error check for invalid moves
	/* Check for side */
	if( board.side != pce[piece].color){
		std::cout << "Invalid move. ";
		( board.side == WHITE ) ? std::cout << "White " : std::cout << "Black ";
		std::cout << "to move.\n";
		return false;
	}

	/* Don't move an empty piece */
	if( piece == NONE ){
		std::cout << "Invalid move. Empty square.\n";
		return false;
	}
	
	/* Can't take your own piece */
	if( toColor == board.side ){
		std::cout << "Invalid move. Don't take your own piece.\n";
		std::cout << "The to color is: " << toColor << "\n";
		std::cout << "The side is: " << board.side << "\n";
		return false;

	}
	
	/* If mostly legal and castling check specifically for castling */
	if( board.castling ) {
		if( checkCastle() ){
			if( board.toSq - board.frSq > 0 )
				board.toSq++;
			else 
				board.toSq--;
			return true;
		}
		else return false;
	}

	/* 	Valid move checks	*/
	/* 	Knight valid check (NVC) */ 
	if( pce[piece].type == KNIGHT ){
		int knightLegal[8];
		knightLegal[0] = (board.newfrSq - 21);
		knightLegal[1] = (board.newfrSq - 19);
		knightLegal[2] = (board.newfrSq - 12);
		knightLegal[3] = (board.newfrSq -  8);
		knightLegal[4] = (board.newfrSq +  8);
		knightLegal[5] = (board.newfrSq + 12);
		knightLegal[6] = (board.newfrSq + 19);
		knightLegal[7] = (board.newfrSq + 21);

		for( int index = 0; index < 8; index++ ){
			if( knightLegal[index] == board.newtoSq )
				return true;
		}
		
		std::cout << "Invalid move. Knights don't move like that.\n";
		return false;
	}

	/* Rook Valid Check (RVC) */
	if( pce[piece].type == ROOK ){
		int indexSq, checkPiece, diff, absDiff, slide;
		diff = ( (board.newtoSq - board.newfrSq) % 10 );
		absDiff = abs(board.newtoSq - board.newfrSq);
	
		if( diff != 0 && (absDiff > 7) ){		//Eliminates impossible rook moves
			std::cout << "Invalid move. Rooks don't move like that.\n";
			return false;
		}
		if( diff == 0 )					//Defines which way rook is sliding
			( board.newtoSq > board.newfrSq ) ? slide = 10 : slide = -10;
		else ( board.newtoSq > board.newfrSq ) ? slide = 1 : slide = -1;	

		//Check the direction the rook is moving
		for( indexSq = (board.newfrSq + slide); indexSq != board.newtoSq; indexSq += slide ){
			checkPiece = board.sq[indexSq];
			toColor = getColor(indexSq);
			if( checkPiece == board.newtoSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. Rooks can't move through piece.\n";
				return false;
			}
			if( checkPiece == -1 ){
				std::cout << "Invalid move. Offboard square.\n";
				return false;
			}
		}
	}

	/* Bishop Valid Check (BVC) */
	if( pce[piece].type == BISHOP ){
		int indexSq, checkPiece, diff, absDiff, slide;
		diff = (board.newtoSq - board.newfrSq);
		absDiff = abs(board.newtoSq - board.newfrSq);
		
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
		for( indexSq = (board.newfrSq + slide); indexSq != board.newtoSq; indexSq += slide ){
			checkPiece = board.sq[indexSq];
			toColor = getColor(indexSq);
			if( checkPiece == board.newtoSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. Bishops can't move through piece.\n";
				return false;
			}
			if( checkPiece == -1 ){
				std::cout << "Invalid move. Offboard Square.\n";
				return false;
			}
		}
	}

	/* Queen Valid Check (QVC) */	
	if( pce[piece].type == QUEEN ){
		int indexSq, checkPiece, diff, absDiff, slide;
		diff = (board.newtoSq - board.newfrSq);
		absDiff = (abs(board.newtoSq - board.newfrSq));
	
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
		for( indexSq = (board.newfrSq + slide); indexSq != board.newtoSq; indexSq += slide ){
			checkPiece = board.sq[indexSq];
			toColor = getColor(indexSq);
			if( indexSq == board.newtoSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. Queen can't move through piece.\n";
				return false;
			}
			if( checkPiece == -1 ){
				std::cout << "Invalid move. Offboard Square.\n";
				return false;
			}
		}
	
	}

	/* King Valid Check (KVC) */
	if( pce[piece].type == KING ){
		int indexSq, checkPiece, diff, absDiff, slide;
		diff = (board.newtoSq - board.newfrSq);
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
		for( indexSq = (board.newfrSq + slide); indexSq != board.newtoSq; indexSq += slide ){
			checkPiece = board.sq[indexSq];
			toColor = getColor(indexSq);
			if( indexSq == board.newtoSq ) return true;
			if( toColor != 0 ){
				std::cout << "Invalid move. King can't move through piece.\n";
				return false;
			}
			if( checkPiece == -1 ){
				std::cout << "Invalid move. Offboard Square.\n";
				return false;
			}
		}
	}
	
	/* Pawn Valid Check (PVC) */		
	if( pce[piece].type == PAWN ){
		int checkPiece, diff, absDiff, piece, toValue, toColor, slide;
		piece = board.sq[board.newfrSq];
		toValue = board.sq[board.newtoSq];
		toColor = getColor(board.newtoSq);
		diff = board.newtoSq - board.newfrSq;;
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
		if( board.newtoSq == -1 ){
			std::cout << "Invalid move. Can't move offboard.\n";
			return false;
		}
		
		/* Forward capture check */
		if( absDiff == 10 ){
			if( toColor != EMPTY ){
				std::cout << "Invalid move. Pawn can't capture forwards.\n";
				std::cout << toColor;
				return false;
			}
			else return true;
		}

		/* Legal capture */
		if( ( absDiff == 9 || absDiff == 11 )){
			std::cout << board.enPas << "\n";
			if( toColor != board.side && toColor != EMPTY ) return true;
			else if( toColor == EMPTY ){
				if( board.enPas == board.newtoSq ) return true;
				else{
					std::cout << "Invalid move. Pawns must capture diagonally.\n";
					return false;
				}
			}			
		} 
		
		/* Legalizes two squares on first pawn move */
		if( absDiff == 20 ){
			if( toColor != EMPTY ){
				std::cout << "Invalid move. Pawns can't capture forwards.\n";
				return false;
			} 
			if( board.side == WHITE && board.newfrSq > H2 ){
				std::cout << "Invalid move. Pawns can only move two squares on their first move.\n";
				return false;
			}
			else if( board.side == BLACK && board.newfrSq < A7 ){
				std::cout << "Invalid move. Pawns can only move two squares on their first move.\n";
				return false;
			} 
			( board.side == WHITE ) ? slide = 10: slide = -10;
			for( checkPiece = (board.newfrSq + slide); checkPiece != board.newtoSq; checkPiece += slide ){
				toValue = board.sq[checkPiece];
				if( toValue != EMPTY ){
					std::cout << "Invalid move. Piece be in the way.\n";
					return false;
				}
				if( checkPiece == board.newtoSq ) return true;
			}
		}
	}

	return true;
}

/*  checkCheck function
 *  checks if the users move put his own king in check
 *  not if he put the opponents king in check.
 *  Search code (FCC)					 */
bool checkCheck(){
	int kingSq, slide, index, toColor, toType, checkPiece;
	int knightLegal[8] = { 21, 12, -8, -19, -21, -12, 8, 19 };	
	int moveDir[9] = { UP, UPRT, RT, DWNRT, DWN, DWNLEFT, LEFT, UPLEFT, BREAK };

	(board.side == WHITE) ? kingSq = pce[wK].pos: kingSq = pce[bK].pos;

	index = 0;
	/* Check the direction of movement */
	for( slide = moveDir[index]; slide != BREAK; index++ ){
		checkPiece = 0;
		slide = moveDir[index];
		if( slide == BREAK ) break;
		for( int indexSq = (kingSq + slide); checkPiece != OFFBOARD; indexSq += slide ){ 
			checkPiece = board.sq[indexSq];
			toColor = getColor(indexSq);
			toType = getType (indexSq);
				
			if( checkPiece == OFFBOARD ){
				break;
			}

			else if( toColor == board.side ){	
				break;
			}
			
			else if( toColor != board.side ){
				if( toType == KING ){
					if( abs(indexSq - kingSq) < 11 ){
						return true;
					}
				}
				if( toType == PAWN ){	
					if( (abs(indexSq - kingSq) == 9 || abs(indexSq - kingSq) == 11) && toType == PAWN ){
						if( board.side == WHITE ){
							if( (indexSq - kingSq) > 0 ){
								return true;
							}
						}
						else if( board.side == BLACK ){
							if( (indexSq - kingSq) < 0 ){
								return true;
							}
						}
					}
					break;
				}
				if( toType == BISHOP || toType == QUEEN ){
					if( abs(slide) % 9 == 0 || abs(slide) % 11 == 0 ){
						return true;
					}
				}
				if( toType == ROOK || toType == QUEEN ){
					if( abs(slide) % 10 == 0 || slide == RT || slide == LEFT ){
						return true;
					}
				}
			}
		}
	}
	
	//After check for sliding checks, check for knight checks, check.				
	for( int index = 0; index < 8; index++ ){
		int checkSq = (kingSq + knightLegal[index]);
		int toColor, toType;

		toColor = getColor( checkSq );
		toType = getType( checkSq );

		if( (toColor != board.side) && (toType == KNIGHT) ){
			return true;
		}
	}
	return false;	

}

/* BCC */	
bool checkCastle(){
	int shift, piece, rookSq, diff, save1, save2, store1, store2;
	int* mF;
	int* mT;
	store1 = board.frSq;
	store2 = board.toSq;
	mF = &(board.newfrSq);
	mT = &(board.newtoSq);
	save1 = *mF;
	save2 = *mT;
	diff = *mT - *mF;
	piece = getPiece(*mF);
	
	//Test
	//std::cout << "Test in checkCastle\n";
	
	//Define kingside or queenside rook squares
	if( diff > 0 ){
		rookSq = *mF + 3;
	}
	else{ 
		rookSq = *mF - 4;
	}

	if( getType(*mF) != KING ){
		return false;
	}	

	if( getType(*mF) == KING && getType(rookSq) == ROOK ){ 
		if( pce[piece].moved > 0 || pce[getPiece(rookSq)].moved > 0 ){
			return false;
		}	
	}
	
	/* Set shift of king movement */
	if ( diff > 0 ){
		shift = 1;
	}
	else{
		 shift = -1;
	}

	/* Check if there are any piece in the way */
	for( int i = (*mF + shift); i != rookSq; i += shift ){
		if( getPiece(i) != EMPTY ){
			return false;
		}
	}

	//Check initial castling position
	if( checkCheck() )
		 return false;
	//Set board.castling to false to allow checking of check for normal king movement.
	board.castling = false;
	board.frSq = *mF;
	board.toSq = *mT;
	makeMove();
	if( checkCheck() ){
		unmakeMove();
		board.frSq = store1;
		board.toSq = store2;
		return false;
	}
	unmakeMove();
	board.frSq = save1;
	board.toSq = save2;

	*mT += shift;
	board.frSq = *mF;
	board.toSq = *mT;
	genFlag = true;
	makeMove();
	if( checkCheck() ){
		unmakeMove();
		board.frSq = store1;
		board.toSq = store2;
		genFlag = false;
		return false;
	}
	unmakeMove();	//Bug disappearing king
	board.frSq = store1;
	board.toSq = store2;
	
	//Reset castling to true to allow final moving of piece (better way to do this?)
	genFlag = false;	
	return true;				
}	

/* Checks for check by moving piece, check that position for check, then unmaking */
bool moveCheck(){
	bool retVal;
	int store1, store2;
	store1 = board.frSq;
	store2 = board.toSq;

	if( !board.castling ){
		board.frSq = board.newfrSq;
		board.toSq = board.newtoSq;
		makeMove();
		if( checkCheck() ) retVal = true;
		else retVal = false;
		unmakeMove();
		board.frSq = store1;
		board.toSq = store2;
	}
	else retVal = false;

	return retVal;
}
