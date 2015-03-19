 //move.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "board.h"
#include <cmath>
#include "legal.h"
#include "debug.h"
#include "eval.h"

//(VMM)
void makeMove(){
	//std::cout << "In makeMove()\n";
	ply++;
	//Set all flags to false;
	bool cFlag = false, eFlag = false, pFlag = false, sFlag = false;
	
	//Determine truthfulness of flags
	int diff = board.toSq - board.frSq;
	if( getType(board.frSq) == KING && abs(diff) == 2 && !genFlag ){
		cFlag = true;
		std::cout << "We castling!\n";
	}
	else if( getType(board.frSq) == PAWN && board.toSq == board.enPas && (abs(diff) == 11 || abs(diff) == 9) ){
		eFlag = true;
		//std::cout << "We passanting!\n";
	}
	else if( getType(board.frSq) == PAWN && (board.toSq / 10 == 9 || board.toSq / 10 == 2) ){
		pFlag = true;
		//std::cout << "We promoting!\n";
	}
	else if( getType(board.frSq) == PAWN && abs(diff) == 20 ){
		sFlag = true;
		//std::cout << "We making passant squares!\n";
	}

	//Store values of squares
	int piece = board.sq[board.frSq];
	int value = board.sq[board.toSq];
	
	//Move piece
	board.sq[board.frSq] = EMPTY;
	board.sq[board.toSq] = piece;
	
	//Update pieces
	pce[piece].pos = board.toSq;
	//if( piece == 0 )
		//std::cout << "Moving an empty square!\n";
	//std::cout << "Increasing move counter!\n";
	pce[piece].moved++;
	pce[value].pos = DEAD;
	pce[value].life = false;

	//Castling
	if( cFlag ){
		int rook = 0;
		//Kingside
		if( diff > 0 ){
			rook = board.sq[board.toSq + 1];
			board.sq[board.toSq + 1] = EMPTY;	
			board.sq[board.toSq - 1] = rook;	
			pce[rook].pos = board.toSq - 1;
		}
		//Queenside
		else if( diff < 0 ){
			rook = board.sq[board.toSq - 2];
			board.sq[board.toSq - 2] = EMPTY;
			board.sq[board.toSq + 1] = rook;
			pce[rook].pos = board.toSq + 1;
		}
		pce[rook].moved++;
	}

	//En Passant
	else if( eFlag ){
		int pawn = 0;
		//std::cout << "Taking enPassant piece!\n"; 
		//White
		if( diff > 0 ){
			//std::cout << "Square being taken is: " << board.toSq - 10 << "\n";
			pawn = board.sq[board.toSq - 10];
			board.sq[board.toSq - 10] = EMPTY;
		}
		//Black
		else if( diff < 0 ){
			pawn = board.sq[board.toSq + 10];
			//std::cout << "Black enPassant\n";
			board.sq[board.toSq + 10] = EMPTY;	
		}
		pce[pawn].life = false;
		pce[pawn].pos = DEAD;
		//std::cout << "Pawns position is: " << pce[pawn].pos << "\n";
	 }

	//Promotion
	if( pFlag ){
		pce[piece].type = QUEEN;
		board.enPas = 117;
	}

	//Set enPassant square
	if( sFlag ){
		board.enPas = (board.side == WHITE) ? board.toSq - 10: board.toSq + 10;
		//std::cout << "enPassant square is: " << board.enPas << "\n";
	}
	else 
		board.enPas = 0; 

	//Add to undo structure
	undo.push_back({board.frSq * 100 + board.toSq, board.enPas, piece * 100 + value});

 /* Old makemove function
	//std::cout << "TEST\n";
	int piece = 0, toVal = 0;
	board.oldfrSq = board.frSq;
	board.oldtoSq = board.toSq;	
	ply++;
	
	//Castling
	if((getType(board.frSq) == KING && abs(board.toSq - board.frSq) == 2) && !genFlag){
		if( !genFlag ){
			int king, rook, diff, rookFrom = 0, rookTo = 0, kingTo = 0; 
			toVal = 0;
			diff = (board.toSq - board.frSq);
			king = board.sq[board.frSq];
			piece = king;
	//std::cout << "TESTTEST\n";
			//If diff is positive, then castling is kingside.
			if( diff > 0){
				 rookFrom = board.frSq + 3;
				 rookTo = board.frSq + 1;
				 kingTo = board.frSq + 2;
			}

			//likewise for queenside
			else if( diff < 0){
				rookFrom = board.frSq - 4;
				rookTo = board.frSq - 1;
				kingTo = board.toSq;
			}
			else
				std::cout << "What is happening?\n";
			rook = board.sq[rookFrom];
			board.oldtoSq = kingTo;
			board.storePiece = rook;
			board.storeSq = rookFrom;
			board.oldPiece = king;
			board.oldVal = rook;

			//Set positions and attributes of king and rook before move.
			//piece = board.sq[board.frSq];
			pce[piece].pos = kingTo;
			pce[rook].pos = rookTo;
			if( piece != EMPTY){
				pce[piece].moved++;
			}
//std::cout << "TESTTESTTEST!\n";
			if( rook != EMPTY )
				pce[rook].moved++;
			board.sq[board.frSq] = EMPTY;
			board.sq[kingTo] = king;
			board.sq[rookFrom] = EMPTY;
			board.sq[rookTo] = rook;
		}	
	}	
	
	else{
		int diff;
		diff = board.toSq - board.frSq;
		piece = board.sq[board.frSq];
		toVal = board.sq[board.toSq];
		board.oldPiece = piece;
		board.oldVal = toVal;
		board.sq[board.frSq] = EMPTY;
		board.sq[board.toSq] = piece;
	if( toVal < 0 || toVal > 32 ){
		 std::cout << "WRONGWRONGWRONGWRONG!\n";
		 std::cout << "toVal is: " << toVal << "\n";
		 std::cout << "frSq: " << board.frSq << " toSq: " << board.toSq << "\n";
		std::cout << "Piece: " << piece << "\n";
		boardDebug();
	}
	//std::cout << "Piece is: " << piece << "\n";
	//std::cout << "Before toVal is: " << toVal << "\n";
	//std::cout << "frSq: " << board.frSq << " toSq: " << board.toSq << "\n";
		pce[toVal].pos = DEAD;
	//std::cout << "After toVal\n";
		pce[toVal].life = false;
	//std::cout << "TESTTESTTESTTEST!!!\n";
		//Quick cover for promotions
		if( getType(board.toSq) == PAWN && (board.toSq > 91 || board.toSq < 31) ){
			pce[board.sq[board.toSq]].type = QUEEN;
		} 
		//Remove the capture enPassant pawn
		if( (abs(board.toSq - board.frSq) == 11 ||  abs(board.toSq - board.frSq) ) && getType(board.toSq) == PAWN && toVal == EMPTY){
			int enPiece, enSq;
			if( diff > 0 ){
				enPiece = board.sq[board.toSq - 10];
				enSq = board.toSq - 10;
				board.sq[board.toSq - 10] = EMPTY;
				pce[enPiece].pos = DEAD;
				pce[enPiece].life = false;
			}
			else {
				enSq = board.toSq + 10;
				enPiece = board.sq[board.toSq + 10];
				board.sq[board.toSq + 10] = EMPTY;
				pce[enPiece].pos = DEAD;
				pce[enPiece].life = false;
			}
			board.storePiece = enPiece;
			board.storeSq = enSq;
			board.enpasFlag = true;
		}

		pce[piece].pos = board.toSq;
		if( piece != EMPTY )
			pce[piece].moved++;
		life++;
	}

	
	//Create an enpassant square for the future
	if( getType(board.toSq) == PAWN && abs(board.toSq - board.frSq) == 20 ){
		int diff = board.toSq - board.frSq;	
		if(diff > 0) board.enPas = board.toSq - 10;
		else board.enPas = board.toSq + 10;
	}
	else board.enPas = 0;

	undo.push_back({(board.frSq * 100 + board.toSq), board.enPas, (piece * 100) + toVal});
//std::cout << "TESTTESTEND!!\n";
*/
}

//(VUM)
void unmakeMove(){
	//std::cout << "In unmakeMove!\n";
	ply--;	
	bool cFlag = false, eFlag = false, pFlag = false;
	int diff = 0, piece, value;
	
	//Set squares to use from undo vector
	board.frSq = undo[undo.size() - 1].move/100;
	board.toSq = undo[undo.size() - 1].move%100;
	piece = undo[undo.size() - 1].piece/100;
	value = undo[undo.size() - 1].piece%100;
	board.enPas = undo[undo.size() - 2].enPas;

	diff = board.toSq - board.frSq;
	
	//Set flags
	if( getType(board.toSq) == KING && abs(diff) == 2 && !genFlag )
		cFlag = true;
	if( getType(board.toSq) == PAWN && (abs(diff) == 11 || abs(diff) == 9) && value == EMPTY ){
		eFlag = true; 
		//std::cout << "unmaking enPassant!\n";
	}
	//Add promotion square later
	if( board.enPas == 117 )
		pFlag = true; 

	//Unmake move
	board.sq[board.frSq] = piece;
	board.sq[board.toSq] = value;
	//std::cout << "Decreasing move counter!\n";
	pce[piece].moved--;
	pce[piece].pos = board.frSq;
	if( value != EMPTY )
		pce[value].life = true;
	pce[value].pos = board.toSq;

	//Castling
	if( cFlag ){
		int rook = 0;
		//Kingside
		if( diff > 0 ){
			rook = board.sq[board.toSq - 1];
			board.sq[board.toSq - 1] = EMPTY;
			board.sq[board.toSq + 1] = rook;	
			pce[rook].pos = board.toSq + 1;
		}
		else if( diff < 0 ){
			rook = board.sq[board.toSq + 1];
			board.sq[board.toSq + 1] = EMPTY;
			board.sq[board.toSq - 2] = rook;
			pce[rook].pos = board.toSq - 2;
		}
		pce[rook].moved--;
	}

	//enPassant
	if( eFlag ){
		int pawn = 0;
		//White
		if( diff > 0 ){
			pawn = 24 + board.toSq % 10;
			board.sq[board.toSq - 10] = pawn;
			pce[pawn].pos = board.toSq - 10;
		}
		else if( diff < 0 ){
			pawn = 8 + board.toSq % 10;
			board.sq[board.toSq + 10] = pawn;
			pce[pawn].pos = board.toSq + 10;
		}
		pce[pawn].life = true;
	}

	//Promotion
	if( pFlag ){
		pce[piece].type = PAWN;
		//std::cout << "No cover for promotions yet!\n";
	}

	undo.pop_back();
/* Old unmake function 
	//Unmake castling
	if((getType(board.toSq) == KING && abs(board.toSq - board.frSq) == 2 ) && !genFlag){
		if( !genFlag ){
			int kingSq, diff, king;
			king = (board.side == WHITE) ? wK: bK;
			(board.side == WHITE) ? kingSq = pce[wK].pos: kingSq = pce[bK].pos;
			board.sq[board.toSq] = EMPTY;
			board.sq[board.frSq] = board.oldPiece;
			diff = board.toSq - board.frSq;
			
			if( diff > 0 ){
				board.sq[board.frSq + 1] = EMPTY;
				board.storeSq = kingSq + 1;
				board.storePiece = king + 3;
			}
			else{
				board.sq[board.frSq - 1] = EMPTY;
				board.storeSq = kingSq - 2;
				board.storePiece = king - 4;
			}
			board.sq[board.storeSq] = board.storePiece; 
			pce[board.storePiece].pos = board.storeSq;
			pce[board.oldPiece].pos = board.frSq;
			if( board.oldPiece != EMPTY ){
				pce[board.oldPiece].moved--;
				if( getType(board.storeSq) != PAWN )
					pce[board.storePiece].moved--;
			}
		}
	}
	else{ 
		//Test
		//std::cout << "Error check before bus crash!\n";
		if( board.frSq < 21 || board.frSq > 98 ){
			std::cout << "frSq error: " << board.frSq << "\n";
		}
		if( board.toSq < 21 || board.toSq > 98 ){
			std::cout << "toSq error: " << board.toSq << "\n";
		}
		board.sq[board.toSq] = board.oldVal;
		board.sq[board.frSq] = board.oldPiece;
		if( board.oldVal == OFFBOARD )
			std::cout << "Moving OFFBOARD\n";
		pce[board.oldVal].pos = board.toSq;
		if( board.oldVal != EMPTY )
			pce[board.oldVal].life = true;
		pce[board.oldPiece].pos = board.frSq;
		
		//Revert moves to before move was made for all non empty pieces
		if( board.oldPiece != EMPTY )
			if( pce[board.oldPiece].moved > 0 )
				pce[board.oldPiece].moved--;
		
		//Enpassant undo
		if( getType(board.frSq) == PAWN && getType(board.toSq) == EMPTY && (abs(board.toSq - board.frSq) == 11 || abs(board.toSq - board.frSq) == 9)){
			if( abs(board.toSq - board.frSq) == 11 ){
				if( board.side == WHITE )
					 board.storeSq = board.frSq + 1;
				else
					 board.storeSq = board.frSq - 1;
				
			}
			else if( abs(board.toSq - board.frSq) == 9 ){
				if( board.side == WHITE )
					board.storeSq = board.frSq - 1;
				else
					board.storeSq = board.frSq + 1;
			}

			board.storePiece = (board.side == WHITE) ? 24 + (board.storeSq % 10): 8 + (board.storeSq % 10);
			board.sq[board.storeSq] = board.storePiece;
			pce[board.storePiece].pos = board.storeSq;
			pce[board.storePiece].life = true;
			pce[board.storePiece].moved = 1;
		}
	}
	undo.pop_back();
	
	board.enPas = undo[undo.size() - 1].enPas;
	return;
*/
}

void changeSide(){	
	(board.side == WHITE) ? board.side = BLACK : board.side = WHITE;
	return;
}

void moveGen(std::vector<int>& moveList){
	int piece;

	genPawn();
	genKnight();
	genBishop();
	genRook();
	genKing();
	genCastle();
	genQueen();
	
	//Fill board movelist with pieces movelists
	piece = (board.side == WHITE) ? wqR: bqR;
	moveList.clear();
	for( int i = 0; i < 16; i++ ){
		if( piece == 5 ){
			std::cout << "Adding white kings moves!\n";
			for( int p = 0; p < pce[wK].mL.size(); p++ ){
				std::cout << pce[wK].mL[p] << " ";
			}
		}
		if( pce[piece].life == false ){
			piece++;
			std::cout << "That piece is dead: " << piece << "\n";
			continue;
		}
		for( int j = 0; j < pce[piece].mL.size(); j++ ){
			if( pce[piece].mL[j] % 100 < 21 || pce[piece].mL[j] % 100 > 98 ){
				std::cout << "Move Gen toSq Error: " << pce[piece].mL[j] << "\n";
			}
			/*	
			if( pce[piece].mL[j] > 10000 || pce[piece].mL[j] < 2000 ){
				std::cout << "Move Gen Error: " << pce[piece].mL[j] << "\n";
				std::cout << "Piece is: " << piece << "\n";
			}
			*/
			moveList.push_back(pce[piece].mL[j]);
		}
		piece++;
	}	
	
	if( board.side == WHITE )
		debugAll();

	//Disable sorting until bugs are fixed
	//sortML(moveList);	
}

void genPawn(){	
	int pawn = (board.side == WHITE) ? wPa: bPa;
	int toSq, pSq;
	int slide[4];
	if( board.side == WHITE ){
		slide[0] = 10;
		slide[1] = 20;
		slide[2] = 9;
		slide[3] = 11;
	}
	else{
		slide[0] = -10;
		slide[1] = -20;
		slide[2] = -9;
		slide[3] = -11;
	}

	for( int i = 0;  i < 8; i++ ){
		pce[pawn].mL.clear();
		if( pce[pawn].life == false ){
			pawn++;
			continue;
		}
		pSq = pce[pawn].pos;

		for( int j = 0; j < 2; j++ ){
			toSq = pSq + slide[j];
			if( pce[pawn].moved != 0 && abs(slide[j]) == 20 ){
				//std::cout << "Fail first move, Pawn is: " << pawn << "\n";
				break;
			}
			else if( getColor(toSq) != EMPTY )
				break;
			else 
				pce[pawn].mL.push_back(( pSq * 100 ) + toSq );
		}

		for( int j = 2; j < 4; j++ ){
			toSq = pSq + slide[j];
			
			if( (board.enPas == toSq) && (((board.side ==  WHITE && board.enPas / 10 == 7)) || ((board.side == BLACK && board.enPas / 10 == 4)))){
				pce[pawn].mL.push_back(( pSq * 100 ) + toSq );
				continue;
			}

			if( getColor(toSq) == EMPTY || getColor(toSq) == OFFBOARD )
				continue;
			else if( getColor(toSq) != board.side ){
				pce[pawn].mL.push_back(( pSq * 100 ) + toSq );
				continue;
			}
			else 
				continue;

		}

		pawn++;		
	}	
	
}

void genRook(){
	int rook = (pow(board.side,4) + (board.side - 1));
	int rSq;
	int change = 7;
	int slide[4] = { 10, 1, -10, -1};

	//Loop for both rooks
	for( int i = 0; i < 2; i++){
		pce[rook].mL.clear();
		if( pce[rook].life == false )
			continue;
		rSq = pce[rook].pos;
		if( pce[rook].pos < 21 || pce[rook].pos > 98 ){
			std::cout << "Rook position error: " << pce[rook].pos << "\n";
			std::cout << "Piece is: " << rook << "\n";
		}
		//Loop for directions
		for( int j = 0; j < 4; j++ ){
			//Loop for individual squares
			for( int checkSq = rSq + slide[j]; board.sq[checkSq] != OFFBOARD; checkSq += slide[j]){
				if( getColor(checkSq) == EMPTY ){
					pce[rook].mL.push_back((rSq * 100) + checkSq);
					continue;
				}
				else if( getColor(checkSq) == OFFBOARD )
					break;
				else if( getColor(checkSq) != board.side ){
					pce[rook].mL.push_back((rSq * 100) + checkSq);
					break;
				}
				else if( getColor(checkSq) == board.side ){
					break;
				}
				else 
					pce[rook].mL.push_back((rSq * 100) + checkSq);
			}
		}		
		if(!i)
			rook += change;
	}
	
}

void genKnight(){
	int knight = (pow(board.side,4) + board.side);
	int nSq;
	int change = 5;
	int jump[8] = { -21, -19, -12, -8, 8, 12, 19, 21 };

	//Fill with possible squares	
	for( int i = 0; i < 2; i++ ){
		pce[knight].mL.clear();
		if( pce[knight].life == false )
			continue;
		nSq = pce[knight].pos;
		for( int j = 0; j < 8; j++ ){
			int checkSq = nSq + jump[j];
			if( getColor(checkSq) != board.side && board.sq[checkSq] != OFFBOARD && checkSq != 0 )
				pce[knight].mL.push_back((nSq * 100) + checkSq);
		}
		if(!i)
			knight += change;
	}

	knight -= change;

	return;
}

void genBishop(){
	int bishop = (pow(board.side,4) + (board.side + 1));
	int bSq;
	int change = 3;
	int slide[4] = { 11, 9, -11, -9};

	//Loop for both bishop
	for( int i = 0; i < 2; i++){
		pce[bishop].mL.clear();
		if( pce[bishop].life == false )
			continue;
		bSq = pce[bishop].pos;
		//Loop for directions
		for( int j = 0; j < 4; j++ ){
			//Loop for individual squares
			for( int checkSq = bSq + slide[j]; board.sq[checkSq] != OFFBOARD; checkSq += slide[j]){
				if( getColor(checkSq) == EMPTY ){
					pce[bishop].mL.push_back((bSq * 100) + checkSq);
					continue;
				}
				else if( getColor(checkSq) == OFFBOARD )
					break;
				else if( getColor(checkSq) != board.side ){
					pce[bishop].mL.push_back((bSq * 100) + checkSq);
					break;
				}
				else if( getColor(checkSq) == board.side ){
					break;
				}
				else 
					pce[bishop].mL.push_back((bSq * 100) + checkSq);
			}
		}		
		if(!i)
			bishop += change;
	}
	
}

void genQueen(){
	int queen = (pow(board.side,4) + (board.side + 2));
	int qSq;
	int slide[8] = { 10, 11, 1, -9, -10, -11, -1, 9};

	//Loop for queen
	for( int i = 0; i < 9; i++ ){
		if (queen == wK || queen == bK)
			std::cout << "WHAT THE FUCK i: " << i << '\n';
		if( pce[queen].type == QUEEN ) 
			pce[queen].mL.clear();
		qSq = pce[queen].pos;
		if( pce[queen].life == false || pce[queen].type != QUEEN ){ 
			if( queen != wQ && queen != bQ )
				queen++;
			else queen += 5;
			continue;
		}

		//Loop for directions
		for( int j = 0; j < 8; j++ ){
			//Loop for individual squares
			for( int checkSq = qSq + slide[j]; board.sq[checkSq] != OFFBOARD; checkSq += slide[j]){
				if( getColor(checkSq) == EMPTY ){
					pce[queen].mL.push_back((qSq * 100) + checkSq);
					continue;
				}
				else if( getColor(checkSq) == OFFBOARD )
					break;
				else if( getColor(checkSq) != board.side ){
					pce[queen].mL.push_back((qSq * 100) + checkSq);
					break;
				}
				else if( getColor(checkSq) == board.side ){
					break;
				}
				else 
					pce[queen].mL.push_back((qSq * 100) + checkSq);
			}
		}		
		if( queen != wQ && queen != bQ ){
			std::cout << "Queen is: " << queen << "\n";
			queen++;
		}
		else queen += 5;
	
	}	
}


void genKing(){
	int king = (pow(board.side,4) + (board.side + 3));
	int kSq;
	int slide[8] = { 10, 11, 1, -9, -10, -11, -1, 9 };

	//Loop for king
	pce[king].mL.clear();
	kSq = pce[king].pos;
	if( !pce[king].life ){
		std::cout << "King is dead. GAME OVER\n";
		return;
	}
	//Loop for directions
	for( int j = 0; j < 8; j++ ){
		//Loop for individual squares
		for( int checkSq = kSq + slide[j]; board.sq[checkSq] != OFFBOARD; checkSq += slide[j]){
			if( getColor(checkSq) == EMPTY ){
				pce[king].mL.push_back((kSq * 100) + checkSq);
				std::cout << "Generating king move!\n";
				std::cout << "King is: " << king << "\n";
				break;
			}
			else if( getColor(checkSq) == OFFBOARD )
				break;
			else if( getColor(checkSq) != board.side ){
				pce[king].mL.push_back((kSq * 100) + checkSq);
				break;
			}
			else if( getColor(checkSq) == board.side ){
				break;
			}
			else 
				pce[king].mL.push_back((kSq * 100) + checkSq);
				break;
			
		}
	}		
	
	
}

void genCastle(){
	int frSq, toSq, kingSq, king;
	frSq = board.newfrSq;
	toSq = board.newtoSq;
	king = (board.side == WHITE) ? wK: bK;
	kingSq = (board.side == WHITE) ? pce[wK].pos: pce[bK].pos;
	board.newfrSq = kingSq;
	
	//Test
	std::cout << "Test in genCastle!\n";
	
	//Check kingside
	board.newtoSq = kingSq + 1;
	if(  getColor(board.newtoSq) == EMPTY && getColor(board.newtoSq + 1) == EMPTY && checkCastle() ){
		//std::cout << "Gen castle kingside!\n";
		pce[king].mL.push_back((kingSq * 100 ) + (kingSq + 2));
		std::cout << "mL back: " << pce[king].mL.back() << '\n';
		std::cout << "King is: " << king << "\n";
		std::cout << "Castling generated!\n";
	}

	//Check queenside
	board.newtoSq = kingSq - 1;
	if( getColor(board.newtoSq) == EMPTY  && getColor(board.newtoSq - 1) == EMPTY && getColor(board.newtoSq - 2) == EMPTY && checkCastle() ){
		pce[king].mL.push_back((kingSq * 100 ) + (kingSq - 2));
	}

	
	//Reset fr and to squares
	board.newfrSq = frSq;
	board.newtoSq = toSq;
}

void sortML( std::vector<int> & sortmL ){
	std::vector<int> score;

	score.clear();
	
	//Generate all scores first
	for(int i = 0; i < sortmL.size(); i++ ){
		setMove(sortmL, i);
		makeMove();
		score.push_back(eval());
		unmakeMove();
	}	
	//Test	
	//std::cout << "movelist size is: " << sortmL.size() << "\n";
	//std::cout << "scorelist size is: " << score.size() << "\n";	
	if( sortmL.size() == 0 ) 
		return;
	//Sort them
	int count, store;
	do{
		count = 0;
		for( int i = 0; i < sortmL.size() - 1; i++ ){
			if( score[i + 1] > score[i] ){
				store = score[i];
				score[i] = score[i + 1];
				score[i + 1] = store;
				store = sortmL[i];
				sortmL[i] = sortmL[i + 1];
				sortmL[i + 1] = store;
				count++; 
			}
		} 
	}while( count > 0 );
	
}
