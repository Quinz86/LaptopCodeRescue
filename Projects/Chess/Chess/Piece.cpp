#include "Piece.h"
#include "Board.h"
#include "Square.h"

//static
Board* Piece::b = nullptr;
void Piece::setBoard(Board* bn) {
	b = bn;
}


//constructor
Piece::Piece(bool w) {
	white = w;
	moves = std::vector<SDL_Point>();
	hasMoved = false;
}

bool Piece::isWhite() {
	return white;
}
void Piece::flipColor() {
	white = !white;
}

std::vector<SDL_Point>* Piece::getValidMoves() {
	return &moves;
}
void Piece::updateMoves(int x, int y) {
	moves.clear();
	findMoves(x,y);
}

void Piece::setMoved(bool m) {
	hasMoved = m;
}