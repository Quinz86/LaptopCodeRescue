#include "Square.h"
#include "Piece.h"

//constructor
Square::Square() {
	occupant = nullptr;
}
Square::~Square() {
	delete occupant;
}

Piece* Square::getOccupant() {
	return occupant;
}
void Square::setOccupant(Piece* p) {
	occupant = p;
}