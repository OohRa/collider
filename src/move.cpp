//move.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "board.h"
#include <cmath>
#include "legal.h"

//(VMM)
void makeMove(){
	int piece, toVal;
	board.oldfrSq = board.frSq;
	board.oldtoSq = board.toSq;	
	
	/* Makes the users move */
	if( board.castling ){
		int king, rook, diff, rookFrom, rookTo, kingTo; 
		diff = (board.toSq - board.frSq);
		king = board.sq[board.frSq];

		//If diff is positive, then castling is kingside.
		if( diff > 0){
			 rookFrom = board.frSq + 3;
			 rookTo = board.frSq + 1;
			 kingTo = board.frSq + 2;
		}

		//likewise for queenside
		else{
			rookFrom = board.frSq - 4;
			rookTo = board.frSq - 1;
			kingTo = board.toSq;
		}
		rook = board.sq[rookFrom];
		board.oldtoSq = rookTo;
		board.storePiece = rook;
		board.storeSq = rookFrom;
		board.oldPiece = king;
		board.oldVal = rook;

		//Set positions and attributes of king and rook before move.
		piece = board.sq[board.frSq];
		pce[piece].pos = kingTo;
		pce[rook].pos = rookTo;
		pce[piece].moved++;
		pce[rook].moved++;

		board.sq[board.frSq] = EMPTY;
		board.sq[kingTo] = king;
		board.sq[rookFrom] = EMPTY;
		board.sq[rookTo] = rook;
		
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
		pce[toVal].pos = DEAD;
		pce[toVal].life = false;

		//Quick cover for promotions
		if( getType(board.toSq) == PAWN && (board.toSq > 91 || board.toSq < 31) ){
			board.sq[board.toSq] = (board.side == WHITE) ? wQ : bQ;
		} 
		//Remove the capture enPassant pawn
		if( board.enPas == board.toSq && getType(board.toSq) == PAWN){
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

		/* Update piecelist */
		pce[piece].pos = board.toSq;
		pce[piece].moved++;
		life++;
	}

	
	//Create an enpassant square for the future
	if( getType(board.toSq) == PAWN && abs(board.toSq - board.frSq) == 20 ){
		int diff = board.toSq - board.frSq;	
		if(diff > 0) board.enPas = board.toSq - 10;
		else board.enPas = board.toSq + 10;
		//Debug
	}
}

//(VUM)
void unmakeMove(){

	if( !board.castling ){

	/* Unmakes the users move */
	board.sq[board.toSq] = board.oldVal;
	board.sq[board.frSq] = board.oldPiece;

	pce[board.oldVal].pos = board.toSq;
	if( board.oldVal != EMPTY )
		pce[board.oldVal].life = true;
	pce[board.oldPiece].pos = board.frSq;
	pce[board.oldPiece].moved--;
	if( getType(board.frSq) == PAWN && getType(board.toSq) == EMPTY && abs(board.toSq - board.frSq) == 11){
		board.sq[board.storeSq] = board.storePiece;
		pce[board.storePiece].pos = board.storeSq;
		pce[board.storePiece].life = true;
	}
	}
	else if( board.castling ){
		int kingSq, diff;
		(board.side == WHITE) ? kingSq = pce[wK].pos: kingSq = pce[bK].pos;
		board.sq[board.toSq] = EMPTY;
		board.sq[board.frSq] = board.oldPiece;
		board.sq[board.storeSq] = board.storePiece;
		diff = board.toSq - board.frSq;
		if( diff > 0 ) board.sq[board.frSq + 1] = EMPTY;
		else board.sq[board.frSq - 1] = EMPTY;

		pce[board.storePiece].pos = board.toSq;
		pce[board.oldPiece].pos = board.frSq;
		pce[board.oldPiece].moved--;
		pce[board.storePiece].moved--;
	/*	if( getType(kingSq + 1) == ROOK && getColor(kingSq + 1) == board.side){
			board	
		{	*/	
	}

}

void changeSide(){	
	(board.side == WHITE) ? board.side = BLACK : board.side = WHITE;
	board.enpasFlag = false;
}

void moveGen(){
	int piece;

	genKnight();
	genBishop();
	genQueen();
	genPawn();
	genRook();
	genKing();
	genCastle();

	//Fill board movelist with pieces movelists
	piece = (board.side == WHITE) ? wqR: bqR;
	for( int i = 0; i < 16; i++ ){
		for( int j = 0; j < pce[piece].mL.size(); j++ ){
			board.mL.push_back(pce[piece].mL[j]);
		}
		piece++;
	}	
}

void genPawn(){	
	int pawn = (board.side == WHITE) ? wPa: bPa;
	int toSq, pSq;
	int slide[4];
	if( board.side == WHITE){
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
		pSq = pce[pawn].pos;
		for( int j = 0; j < 2; j++ ){
			toSq = pSq + slide[j];
			if( pce[pawn].moved != 0 && abs(slide[j]) == 20 )
				break;
			else if( getColor(toSq) != EMPTY )
				break;
			else 
				pce[pawn].mL.push_back(( pSq * 100 ) + toSq );
		}
		for( int j = 2; j < 4; j++ ){
			toSq = pSq + slide[j];
			if( toSq != board.enPas )
				continue;
			else 
				pce[pawn].mL.push_back(( pSq * 100 ) + toSq );
		}
		pawn++;		
	}	

	pawn -= 8;

	//Output Pawn movelist
	for( int i = 0; i < 8; i++ ){
		std::cout << "Pawn " << i + 1 << " movelist is: ";
		for( int j = 0; j < pce[pawn].mL.size(); j++ ){
			std::cout << pce[pawn].mL[j] << " ";
		}
		std::cout << "\n";
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
		rSq = pce[rook].pos;
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
	
	//Test output of movelists
	rook -= change;
	for( int i = 0; i < 2; i++){
		std::cout << "The Rooks movelists are: "; 
		for( int j = 0; j < pce[rook].mL.size(); j++ ){
			std::cout << pce[rook].mL[j] << " ";
		}
		std::cout << "\n";
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
		if( pce[knight].life == false )
			continue;
		nSq = pce[knight].pos;
		pce[knight].mL.clear();
		for( int j = 0; j < 8; j++ ){
			int checkSq = nSq + jump[j];
			if( getColor(checkSq) == !board.side && board.sq[checkSq] != OFFBOARD)
				pce[knight].mL.push_back((nSq * 100) + checkSq);
		}
		if(!i)
			knight += change;
	}

	knight -= change;
	for( int j = 0; j < 2; j++ ){
		std::cout << "Knight Movelist is: ";
		for( int i = 0; i < pce[knight].mL.size(); i++ ){
			std::cout << pce[knight].mL[i] << " ";
		}
		knight +=change;
		std::cout << "\n";
	}

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
	
	//Test output of movelists
	bishop -= change;
	for( int i = 0; i < 2; i++){
		std::cout << "The Bishop movelists are: "; 
		for( int j = 0; j < pce[bishop].mL.size(); j++ ){
			std::cout << pce[bishop].mL[j] << " ";
		}
		std::cout << "\n";
		bishop += change;
	}
}

void genQueen(){
	int queen = (pow(board.side,4) + (board.side + 2));
	int qSq;
	int slide[8] = { 10, 11, 1, -9, -10, -11, -1, 9};

	//Loop for queen
	pce[queen].mL.clear();
	qSq = pce[queen].pos;

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
	
	
	//Test output of movelists
	std::cout << "The Queen movelist are: "; 
	for( int j = 0; j < pce[queen].mL.size(); j++ ){
		std::cout << pce[queen].mL[j] << " ";
	}
	std::cout << "\n";
	
}

void genKing(){
	int king = (pow(board.side,4) + (board.side + 2));
	int kSq;
	int slide[8] = { 10, 11, 1, -9, -10, -11, -1, 9 };

	//Loop for queen
	pce[king].mL.clear();
	kSq = pce[king].pos;

	//Loop for directions
	for( int j = 0; j < 8; j++ ){
		//Loop for individual squares
		for( int checkSq = kSq + slide[j]; board.sq[checkSq] != OFFBOARD; checkSq += slide[j]){
			if( getColor(checkSq) == EMPTY ){
				pce[king].mL.push_back((kSq * 100) + checkSq);
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
	
	
	//Test output of movelists
	std::cout << "The King movelist are: "; 
	for( int j = 0; j < pce[king].mL.size(); j++ ){
		std::cout << pce[king].mL[j] << " ";
	}
	std::cout << "\n";
}

void genCastle(){
	int frSq, toSq, kingSq, king;
	frSq = board.newfrSq;
	toSq = board.newtoSq;
	king = (board.side == WHITE) ? wK: bK;
	kingSq = (board.side == WHITE) ? pce[wK].pos: pce[bK].pos;
	board.newfrSq = kingSq;
	
	//Check kingside
	board.newtoSq = kingSq + 1;
	if( checkCastle() )
		pce[king].mL.push_back((kingSq * 100 ) + (kingSq + 2));
	//Check queenside
	board.newtoSq = kingSq -1;
	if( checkCastle() )
		pce[king].mL.push_back((kingSq * 100 ) + (kingSq + 2));

	//Display Movelists
	std::cout << "Castling moves are: ";
	for( int i = 0; i < pce[king].mL.size(); i++ ){
		std::cout << pce[king].mL[i] << " ";	
	}
	std::cout << "\n";
	
	//Reset fr and to squares
	board.newfrSq = frSq;
	board.newtoSq = toSq;
}
