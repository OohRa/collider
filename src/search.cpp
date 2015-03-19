//search.cpp

#include <iostream>
#include "primer.h"
#include "move.h"
#include "eval.h"
#include "search.h"
#include "board.h"
#include "display.h"
#include "debug.h"
#include "legal.h"
#include <chrono>

int leaf = 0;
void engine(){
	int score, bestMove, bestScore;
	life = 0;
	score = 0;
	int alpha = -99999;
	int beta = 99999;
	bestScore = -99999;
	bestMove = 0;
	moveGen(board.mL);
	
	//Alpha Beta loop
	auto t1 = std::chrono::high_resolution_clock::now();
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	for( int i = 0; i < board.mL.size(); i++ ){

		setMove(board.mL, i);
		makeMove();
/*
		if( checkCheck() ){
			unmakeMove();
			continue;
		}
*/
		if( slowFlag )
			displayAll();
		life++;	

		//Call to negaMax 
		score = -negaMax( -beta, -alpha , 6 );

		if( score > alpha ){
			bestMove = i;
			alpha = score;
			bestScore = score;
			std::cout << "New Best Score!\n";
		}

		//std::cout << "AlphaBeta move is: " << board.mL[i] << "\n";
		//std::cout << "AlphaBeta score is: " << score << "\n";
		unmakeMove();
		
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	fsec fs = t2 - t1;
	
	//Statistics
	std::cout << "Collider took: "
		  << fs.count()
		  << " seconds\n";
	std::cout << "At "
		  << life / fs.count()
		  << " nodes per seconds\n";
	std::cout << "For a total of: "
		  << life
		  << " nodes\n";
	std::cout << "With " << leaf << " leaves cut!\n";
	leaf = 0;

	std::cout << "Index is: " << bestMove << "\n";
	std::cout << "The best move is: " << board.mL[bestMove] << "\n";
	std::cout << "With a score of: " << bestScore << "\n";
	std::cout << "movelist size is: " << board.mL.size() << "\n";
	std::cout << "Current score is: ";

	setMove(board.mL, bestMove);
	makeMove();
	changeSide();
	std::cout << eval() << "\n";
}

int negaMax( int alpha, int beta, int depth ){
	int score;	
	std::vector<int> mL;
	if( depth == 0 ){
		changeSide();
		score = eval();
		changeSide();
		//std::cout << "Current score is: " << best << "\n";
		return score;
	}
	changeSide();
	moveGen(mL);
//	debugAll();
	for( int i = 0; i < mL.size(); i++ ){
		setMove(mL, i);
		makeMove();
/*
		if( checkCheck() ){
			unmakeMove();
			continue;
		}
*/
/*
		//Test amount of pawns
		int count = 0;
		for( int j = 0; j < 120; j++ ){
			if( getType(j) == PAWN )
				count++;
			if( count > 17 ){
				std::cout << "WRONGPAWNWRONGPAWNWRONGPAWN!\n";
				std::cout << "Move made was: " << mL[i] << "\n";
			}
			
		}
*/
		if( slowFlag )
			displayAll();
		life++;
		score = -negaMax( -beta, -alpha, depth - 1 );

		//AlphaBeta pruning
		if( score >= beta ){
			//std::cout << "Leaf pruned!\n";
			leaf++;	
			unmakeMove();
			changeSide();
			return beta;
		}
			
		if( score > alpha )
			alpha = score;

		unmakeMove();
	}

	changeSide();
	return alpha;
	
}
