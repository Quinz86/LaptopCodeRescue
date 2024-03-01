#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(bool w);

	PieceType getPieceType();
private:
	void findMoves(int x, int y);

};