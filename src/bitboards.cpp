//bitboards.cpp
// Will add in actual bitboard functionality
// after completion of basic chess engine

#include "primer.h"
#include "bitboards.h"

/* Used to set a certain bit in a bitboard */
void setBit( int sq, U64 &bbAddress ){
	U64 setBit = 1;
	U64 bb = bbAddress;
	setBit <<= sq;
	bb = bb | setBit;
	bbAddress = bb;
}
 
