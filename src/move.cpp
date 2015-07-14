//move.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "board.h"
#include <cmath>
#include "legal.h"
#include "debug.h"
#include "eval.h"
#include "sdl.h"

//(VMM)
void makeMove(){
	ply++;

	//Set all flags to false;
	bool cFlag = false, eFlag = false, pFlag = false, sFlag = false;
	
	//Determine truthfulness of flags
	int diff = board.toSq - board.frSq;
	if( getType(board.frSq) == KING && abs(diff) == 2 && !genFlag ){
		cFlag = true;
		//std::cout << "We castling!\n";
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

	//Update material
	board.material[getOpp()] -= pce[value].value;

	//Move piece
	board.sq[board.frSq] = EMPTY;
	board.sq[board.toSq] = piece;
	
	//Bitboard move
	int indexSq = indexA.sq[board.toSq];
	pce[piece].bitboard = 0;
	pce[piece].bitboard++;
	pce[piece].bitboard <<= indexSq;
	pce[value].bitboard = 0;

	//Update pieces
	pce[piece].pos = board.toSq;
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
		pce[rook].bitboard = 0;
		pce[rook].bitboard++;
		pce[rook].bitboard <<= indexA.sq[pce[rook].pos];
		board.castled[board.side] = true;
	}
	
	//En Passant
	else if( eFlag ){
		int pawn = 0;

		//White
		if( diff > 0 ){
			pawn = board.sq[board.toSq - 10];
			board.sq[board.toSq - 10] = EMPTY;
		}

		//Black
		else if( diff < 0 ){
			pawn = board.sq[board.toSq + 10];
			board.sq[board.toSq + 10] = EMPTY;	
		}
		pce[pawn].life = false;
		pce[pawn].pos = DEAD;
		pce[pawn].bitboard = 0;
		board.material[getOpp()] -= pce[pawn].value;
	 }
	
	//Promotion
	if( pFlag ){
		pce[piece].type = QUEEN;
		pce[piece].value = QVAL;
		board.material[board.side] += (QVAL-PVAL);
		board.enPas = 117;
	}

	//Set enPassant square
	else if( sFlag ){
		board.enPas = (board.side == WHITE) ? board.toSq - 10: board.toSq + 10;
	}
	else 
		board.enPas = 0; 

	//Add to undo structure
	undo.push_back({board.frSq * 100 + board.toSq, board.enPas, piece * 100 + value});

	updateBB();
}

//(VUM)
void unmakeMove(){
	ply--;	
	bool cFlag = false, eFlag = false, pFlag = false;
	int diff = 0, piece, value;
	int promote = 0;	

	//Set squares to use from undo vector
	board.frSq = undo[undo.size() - 1].move/100;
	board.toSq = undo[undo.size() - 1].move%100;
	piece = undo[undo.size() - 1].piece/100;
	value = undo[undo.size() - 1].piece%100;
	board.enPas = undo[undo.size() - 2].enPas;
	promote = undo[undo.size() - 1].enPas;
	
	diff = board.toSq - board.frSq;
	
	//Set flags
	if( getType(board.toSq) == KING && abs(diff) == 2 && !genFlag )
		cFlag = true;
	if( getType(board.toSq) == PAWN && (abs(diff) == 11 || abs(diff) == 9) && value == EMPTY ){
		eFlag = true; 
		//std::cout << "unPassanting!\n";
	}
	//Add promotion square later
	if( promote == 117 && getType(board.toSq) == QUEEN ){
		//std::cout << "unPromoting!\n";
		pFlag = true; 
	}

	//Material Count
	board.material[getOpp()] += pce[value].value;

	//Unmake move
	board.sq[board.frSq] = piece;
	board.sq[board.toSq] = value;
	pce[piece].moved--;
	pce[piece].pos = board.frSq;
	if( value != EMPTY )
		pce[value].life = true;
	pce[value].pos = board.toSq;
	pce[piece].bitboard = 0;
	pce[value].bitboard = 0;
	pce[piece].bitboard++;
	pce[piece].bitboard <<= indexA.sq[pce[piece].pos];
	pce[value].bitboard++;
	pce[value].bitboard <<= indexA.sq[pce[value].pos];

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
		pce[rook].bitboard = 0;
		pce[rook].bitboard++;
		pce[rook].bitboard <<= indexA.sq[pce[rook].pos];
		board.castled[board.side] = false;
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
		pce[pawn].bitboard = 0;
		pce[pawn].bitboard++;
		pce[pawn].bitboard <<= indexA.sq[pce[pawn].pos];
		board.material[getOpp()] += pce[pawn].value;
	}

	//Promotion
	if( pFlag ){
		pce[piece].type = PAWN;
		pce[piece].value = PVAL;
		board.material[board.side] -= (QVAL-PVAL);
		//std::cout << "Unpromoting.\n";
	}
	
	undo.pop_back();
	updateBB();
}


void moveGen(std::vector<int>& moveList, bool caps, bool checks ){
	int piece;
	//std::cout << "Move genning!\n";

	moveList.clear();
	moveList.reserve(40);
	genPawn();
	genKnight();
	genBishop();
	genRook();
	genKing();

	//Don't call genCastle if king is off initial square
	if( ((board.side == WHITE && pce[wK].pos == 25) || (board.side == BLACK && pce[bK].pos == 95)) && !checks )
		genCastle();
	genQueen( );

	piece = (board.side == WHITE) ? wqR: bqR;
	//Add captures first
	for( int i = 0; i < 16; i++ ){
		if( piece == 5 ){
			//std::cout << "Adding white kings moves!\n";
			//for( int p = 0; p < pce[wK].mL.size(); p++ ){
				//std::cout << pce[wK].mL[p] << " ";
			//}
		}
		if( pce[piece].life == false ){
			piece++;
			//std::cout << "That piece is dead: " << piece << "\n";
			continue;
		}
		for( int j = 0; j < pce[piece].caps.size(); j++ ){
			if( pce[piece].caps[j] % 100 < 21 || pce[piece].caps[j] % 100 > 98 ){
				std::cout << "Move Gen toSq Error: " << pce[piece].caps[j] << "\n";
				std::cout << "Piece is: " << piece << "\n";
				debugAll();
				SDL_Delay(10000);
			}
			/*	
			if( pce[piece].mL[j] > 10000 || pce[piece].mL[j] < 2000 ){
				std::cout << "Move Gen Error: " << pce[piece].mL[j] << "\n";
				std::cout << "Piece is: " << piece << "\n";
			}
			*/
			moveList.push_back(pce[piece].caps[j]);
		}
		piece++;
	}	
	
	//Test output movelist
	//std::cout << "Movelist before sorting.\n";
/*
	for( int i = 0; i < moveList.size(); ++i ){
		std::cout << moveList[i] << " ";
	}
	std::cout << "\n";
*/

	//Sort captures
	sortCaps( moveList );
	int sizeCaps = moveList.size();

	//Test output movelist
	//std::cout << "Movelist after sorting.\n";
/*
	for( int i = 0; i < moveList.size(); ++i ){
		std::cout << moveList[i] << " ";
	}
	std::cout << "\n";
*/

	//std::cout << "There are: " << moveList.size() << " captures.\n";
	
	if( !caps ){
		//Fill board movelist with pieces movelists
		piece = (board.side == WHITE) ? wqR: bqR;
		for( int i = 0; i < 16; i++ ){
			if( piece == 5 ){
				//std::cout << "Adding white kings moves!\n";
				//for( int p = 0; p < pce[wK].mL.size(); p++ ){
					//std::cout << pce[wK].mL[p] << " ";
				//}
			}
			if( pce[piece].life == false ){
				piece++;
				//std::cout << "That piece is dead: " << piece << "\n";
				continue;
			}
			for( int j = 0; j < pce[piece].mL.size(); j++ ){
				if( pce[piece].mL[j] % 100 < 21 || pce[piece].mL[j] % 100 > 98 ){
					std::cout << "Move Gen toSq Error: " << pce[piece].mL[j] << "\n";
					std::cout << "Piece is: " << piece << "\n";
					debugAll();
					SDL_Delay(10000);
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
		sortML(moveList, sizeCaps);	

	
	}	
	//if( board.side == WHITE )
		//debugAll();

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
		pce[pawn].caps.clear();
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
				pce[pawn].caps.push_back(( pSq * 100 ) + toSq );

				//Test
				//std::cout << "Adding pawn capture.\n";
				continue;
			}

			if( getColor(toSq) == EMPTY || getColor(toSq) == OFFBOARD )
				continue;
			else if( getColor(toSq) != board.side ){
				//Test 
				//std::cout << "Adding pawn capture.\n";
				pce[pawn].caps.push_back(( pSq * 100 ) + toSq );
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
		pce[rook].caps.clear();
		if( pce[rook].life == false ){
			rook += change;
			continue;
		}
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
						pce[rook].caps.push_back((rSq * 100) + checkSq);
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
		pce[knight].caps.clear();
		if( pce[knight].life == false ){
			knight += change;
			continue;
		}
		if( pce[knight].type == NOTYPE )
			std::cout << "MOVEGENBUGKNIGHTS!\n";
		nSq = pce[knight].pos;
		for( int j = 0; j < 8; j++ ){
			int checkSq = nSq + jump[j];
			if( getColor(checkSq) == EMPTY )
				pce[knight].mL.push_back((nSq * 100) + checkSq);
			else if( getColor(checkSq) != board.side && board.sq[checkSq] != OFFBOARD && checkSq != 0 )
				pce[knight].caps.push_back((nSq * 100) + checkSq);
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
		pce[bishop].caps.clear();
		if( pce[bishop].life == false ){
			bishop += change;
			continue;
		}
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
					pce[bishop].caps.push_back((bSq * 100) + checkSq);
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
		//if (queen == wK || queen == bK)
			//std::cout << "WHAT THE FUCK i: " << i << '\n';
		if( pce[queen].type == QUEEN ){
			pce[queen].mL.clear();
			pce[queen].caps.clear();
		}
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
					pce[queen].caps.push_back((qSq * 100) + checkSq);
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
			//std::cout << "Queen is: " << queen << "\n";
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
	pce[king].caps.clear();
	kSq = pce[king].pos;
	if( !pce[king].life ){
		//std::cout << "King is dead. GAME OVER\n";
		return;
	}
	//Loop for directions
	for( int j = 0; j < 8; j++ ){
		//Loop for individual squares
		for( int checkSq = kSq + slide[j]; board.sq[checkSq] != OFFBOARD; checkSq += slide[j]){
			if( board.sq[checkSq] == EMPTY ){
				pce[king].mL.push_back((kSq * 100) + checkSq);
				//std::cout << "Generating king move!\n";
				//std::cout << "King is: " << king << "\n";
				break;
			}
			else if( board.sq[checkSq] == OFFBOARD )
				break;
			else if( getColor(checkSq) != board.side ){
				pce[king].caps.push_back((kSq * 100) + checkSq);
				break;
			}
			else if( getColor(checkSq) == board.side ){
				break;
			}
			else{ 
				pce[king].mL.push_back((kSq * 100) + checkSq);
				std::cout << "Else king addition!\n";
				break;
			}
			
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
	//std::cout << "Test in genCastle!\n";

	//Check that king starts on initial square
	//if( kingSq != 25 || kingSq != 95 )
	//	return;  
	
	//Check kingside
	board.newtoSq = kingSq + 1;
	if(  getColor(board.newtoSq) == EMPTY && board.sq[board.newtoSq + 1] == EMPTY && checkCastle() ){

		//std::cout << "Gen castle kingside!\n";
		pce[king].mL.push_back((kingSq * 100 ) + (kingSq + 2));
		//std::cout << "mL back: " << pce[king].mL.back() << '\n';
		//std::cout << "King is: " << king << "\n";
		//std::cout << "Castling generated!\n";
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

//sortCaps
//Sort captures by least attacker and greatest defender (LAGD)
void sortCaps( std::vector<int> & sortCaps ){
	std::vector<int> score;

	score.clear();
	
	//Generate all differences first
	for(int i = 0; i < sortCaps.size(); i++ ){
		score.push_back(pce[getPiece(sortCaps[i]/100)].value - pce[getPiece(sortCaps[i]%100)].value);
	}	

	//Test	
	//std::cout << "movelist size is: " << sortmL.size() << "\n";
	//std::cout << "scorelist size is: " << score.size() << "\n";	
	if( sortCaps.size() == 0 ) 
		return;
	//Sort them
	int count, store;
	do{
		count = 0;
		for( int i = 0; i < sortCaps.size() - 1; i++ ){
			if( score[i + 1] < score[i] ){
				store = score[i];
				score[i] = score[i + 1];
				score[i + 1] = store;
				store = sortCaps[i];
				sortCaps[i] = sortCaps[i + 1];
				sortCaps[i + 1] = store;
				count++; 
			}
		} 
	}while( count > 0 );
	

}

void sortML( std::vector<int> & sortmL, int size ){
	//Placeholder until I come up with an efficient algorithm
	std::vector<int> sort(size, 0);
	
	int sq = 0, to = 0, piece = 0, type = 0, score = 0;
	//std::cout << "In sortML!\n";
	
	//Score all moves
	for(int i = size; i < sortmL.size(); ++i){
		score = 0;
		sq = indexA.sq[(sortmL[i]/100)];
		to = indexA.sq[(sortmL[i] % 100)];
		piece = getPiece(sortmL[i]/100);
		type = pce[piece].type; 
		if( board.side == BLACK ){
			sq = flip[sq];
			to = flip[to];
		}
		if( type == PAWN ){
			score = pawnTable[to] - pawnTable[sq];
/*
			std::cout << "to val: " << pawnTable[to] << "\n";
			std::cout << "fr val: " << pawnTable[sq] << "\n";
			std::cout << "sq is: " << sq << " to is: " << to << "\n";
			std::cout << "side is: " << board.side << "\n";
			std::cout << "sort move is: " << sortmL[i] << "\n";
*/
		}
		else if( type == KNIGHT )
			score = knightTable[to] - knightTable[sq];
	
		else if( type == BISHOP ){
			score = bishopTable[to] - bishopTable[sq];
		}
		else if( type == ROOK ){
			score = rookTable[to] - rookTable[sq];
		}
		else if( type == QUEEN ){
			score = queenTable[to] - queenTable[sq];
		}
		
		else if( type == KING ) {
			if( ply < 40 )
				score = kingTable1[to] - kingTable1[sq];
			else 
				score = kingTable2[to] - kingTable2[sq];
		}
		sort.push_back(score);
	}

	if( sort.size() == 0 ) 
		return;
	//Sort them
	//std::cout << "Sorting!\n";
	int count, store;
	do{
		count = 0;
		for( int i = size; i < sortmL.size() - 1; i++ ){
			if( sort[i + 1] > sort[i] ){
				store = sort[i];
				sort[i] = sort[i + 1];
				sort[i + 1] = store;
				store = sortmL[i];
				sortmL[i] = sortmL[i + 1];
				sortmL[i + 1] = store;
				count++; 
			}
		} 
	}while( count > 0 );
	//std::cout << "Done sorting!\n";

}

//Clean Movelist
//When the king is in check in the current position
//only search moves the get king out of check.

void cleanList( std::vector<int>& mL ){
	//Loop through movelist and remove moves that don't escape check
	for( int i = 0; i < mL.size(); ++i ){
		setMove(mL, i);
		makeMove();
		if( checkCheck() )
			mL[i] = 0;		
	}

	int i = 0, count = 1;
	while( count != 0 ){
		if( mL[i] == 0 )
			++i;
	}
}

//Update bb
void updateBB(){
	int piece = 0;
	//Update Pieces
	for( int c = WHITE; c <= BLACK; ++c ){
		bb.pawns[c] = 0;
		piece = ( c == WHITE ) ? wPa: bPa;
		for( int i = piece; i <= piece + 7; ++i ){
			bb.pawns[c] |= pce[i].bitboard;
		}

		piece = ( c == WHITE ) ? wqR: bqR;
		bb.rooks[c] = 0;
		bb.rooks[c] |= pce[piece].bitboard | pce[piece + 7].bitboard;  
		bb.pieces[c] = 0;
		bb.pieces[c] |= bb.pawns[c] | bb.rooks[c];
		piece = (c == WHITE ) ? wqN : bqN;
		for( int i = piece; i <= piece + 5; ++i ){
			bb.pieces[c] |= pce[i].bitboard;
		}
		bb.occupiedSquares |= bb.pieces[c];
	}
	bb.emptySquares = ~bb.occupiedSquares;
	
	

} 
