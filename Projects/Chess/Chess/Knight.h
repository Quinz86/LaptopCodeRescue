#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(bool w);

	PieceType getPieceType();
private:
	void findMoves(int x, int y);

};