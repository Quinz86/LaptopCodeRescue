#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(bool w);

	PieceType getPieceType();
private:
	void findMoves(int x, int y);

};
