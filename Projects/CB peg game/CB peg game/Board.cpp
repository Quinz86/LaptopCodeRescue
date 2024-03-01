#include "Board.h"
#include <vector>
#include <math.h>

//static
int Board::getNthTriangularNumber(int s) {
	return ((s)*(s+1))/2;
}
int Board::decodeLNtoP(int l, int n) {
	return (getNthTriangularNumber(l - 1)) + n;
}
//DONT USE THIS
int Board::decodePtoLN(int p) {
	return -1; //is this even possible?
}



//constructors
Board::Board() {
	
}
Board::Board(Board* other) : Board() {
	for (int x = 1; x <= 5; x++) {
		for (int y = 1; y <= x; y++) {
			grid[decodeLNtoP(x,y) - 1] = other->getPegAt(x, y);
		}
	}
	std::vector<Move>* pList = other->getPreviousMoves();
	for (int m = 0; m < pList->size(); m++) {
		previousMoves.push_back(pList->at(m));
	}
}
Board::~Board() {

}


//methods
bool Board::getPegAt(int l, int n) {
	if (l <= 0 || l >= 6 || n <= 0 || n > l) {
		throw std::out_of_range("Outside of Board");
	}
	return grid[decodeLNtoP(l, n) - 1];
}
void Board::setPegAt(int l, int n, bool b) {
	if (l <= 0 || l >= 6 || n <= 0 || n > l) {
		throw std::out_of_range("Outside of Board");
	}
	grid[decodeLNtoP(l, n) - 1] = b;
}
void Board::addMove(Move m) {
	previousMoves.push_back(m);
}
std::vector<Move>* Board::getPreviousMoves() {
	return &previousMoves;
}
int Board::getNumPegsLeft() {
	int count = 0;
	for (int x = 0; x < 15; x++) {
		count += (int)grid[x];
	}
	return count;
}


//toString
std::string Board::toString() {
	std::string toReturn = "";
	for (int x = 1; x <= 5; x++) {
		for (int y = 1; y <= x; y++) {
			toReturn += std::to_string((int)grid[decodeLNtoP(x, y) - 1]) + " ";
		}
		toReturn += "\n";
	}
	return toReturn;
}
