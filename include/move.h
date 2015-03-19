#ifndef MOVE_H
#define MOVE_H

//move.h


//Functions
void makeMove();
void unmakeMove();
void changeSide();
void moveGen(std::vector<int>&);
void genPawn();
void genRook();
void genKnight();
void genBishop();
void genQueen();
void genKing();
void genCastle();
void sortML(std::vector<int>&);


#endif
