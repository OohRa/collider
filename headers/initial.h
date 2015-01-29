#ifndef INITIAL_H
#define INITIAL_H
//initial.h

//Functions
void initialIndexes( indexStruct &indexArray );
void initialBoard( boardStruct &board );
void initialPieces( pieceStruct pieces[], boardStruct &board );
void initialBitboards( bitboardStruct &bb, pieceStruct pieces[] );
int initialSDL(  );
void initializeAll( boardStruct &board, pieceStruct pieces[], indexStruct &indexArray, bitboardStruct &bb );
#endif 
