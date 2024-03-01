#include "King.h"
#include "Board.h"



//constructor
King::King(bool w) : Piece(w) {
	
}


PieceType King::getPieceType() {
	return KING;
}

void King::findMoves(int xo, int yo) {
	//3x3 around king
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i != 0 || j != 0) {
				try {
					if (!(b->getPieceAt(xo+i, yo+j))) {
						moves.push_back({xo+i,yo+j});
					}
				}catch (int err) {
					//not on the board
				}
			}
		}
	}
	//add castles here
	if (!hasMoved) {

	}

}