#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(bool w);

	PieceType getPieceType();
private:
	void findMoves(int x, int y);

};