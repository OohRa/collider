#ifndef MOVE_H
#define MOVE_H

//move.h


//Functions
void makeMove();
void unmakeMove();
inline void changeSide(){	
	(board.side == WHITE) ? board.side = BLACK : board.side = WHITE;
	return;
}
void moveGen(std::vector<int>&, bool caps = false, bool checks = false);
void genPawn();
void genRook();
void genKnight();
void genBishop();
void genQueen();
void genKing();
void genCastle();
void sortML(std::vector<int>&, int size);
void sortCaps(std::vector<int>&);
void updateBB();


#endif
