#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(bool w);

	PieceType getPieceType();
private:
	void findMoves(int x, int y);

};