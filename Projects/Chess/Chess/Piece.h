#pragma once
#include "SDL.h"
#include <vector>
#include "PieceType.h"

class Board;

class Piece {
public:
	Piece(bool w);
	
	
	bool isWhite();
	void flipColor();

	std::vector<SDL_Point>* getValidMoves();
	void updateMoves(int x, int y);
	virtual PieceType getPieceType() = 0;
	
	void setMoved(bool m);
	
	static void setBoard(Board* bn);
protected:
	static Board* b;

	virtual void findMoves(int x, int y) = 0;

	std::vector<SDL_Point> moves;
	bool white;

	bool hasMoved;
	
};