#include "Pawn.h"
#include "Board.h"



//constructor
Pawn::Pawn(bool w) : Piece(w) {

}


PieceType Pawn::getPieceType() {
	return PAWN;
}

void Pawn::findMoves(int xo, int yo) {


}