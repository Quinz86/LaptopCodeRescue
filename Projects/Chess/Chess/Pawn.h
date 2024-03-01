#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(bool w);

	PieceType getPieceType();
private:
	void findMoves(int x, int y);

};