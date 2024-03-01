#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include <fstream>
#include "AllThePieces.h"
#include <iostream>


Board::Board() : Board(8, 8) {
	//add default pieces here
	setPieceAt(0, 0, new Rook(false));
	setPieceAt(1, 0, new Knight(false));
	setPieceAt(2, 0, new Bishop(false));
	setPieceAt(3, 0, new Queen(false));
	setPieceAt(4, 0, new King(false));
	setPieceAt(5, 0, new Bishop(false));
	setPieceAt(6, 0, new Knight(false));
	setPieceAt(7, 0, new Rook(false));
	for (int x = 0; x < 8; x++) {
		setPieceAt(x, 1, new Pawn(false));
		setPieceAt(x, 6, new Pawn(true));
	}
	setPieceAt(0, 7, new Rook(true));
	setPieceAt(1, 7, new Knight(true));
	setPieceAt(2, 7, new Bishop(true));
	setPieceAt(3, 7, new Queen(true));
	setPieceAt(4, 7, new King(true));
	setPieceAt(5, 7, new Bishop(true));
	setPieceAt(6, 7, new Knight(true));
	setPieceAt(7, 7, new Rook(true));
	
}
Board::Board(int w, int h) {
	numPcs = 0;

	grid = std::vector<std::vector<Square*>>();
	for (int x = 0; x < w; x++) {
		grid.push_back( std::vector<Square*>() );
		for (int y = 0; y < h; y++) {
			grid.at(x).push_back(new Square());
		}
	}
	

	Piece::setBoard(this); //maybe not do this here, might not be safe
	//maybe pass a board pointer when they pieces need to compute moves and such???

}

Board::~Board() {
	std::fstream fileTest;
	//fileTest.open()

	for (int x = 0; x < getWidth(); x++) {
		for (int y = 0; y < getHeight(); y++) {
			delete grid.at(x).at(y);
		}
	}
}

int Board::getWidth() {
	return grid.size();
}
int Board::getHeight() {
	return grid.at(0).size();
}

Piece* Board::getPieceAt(int x, int y)
{
	if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
		return grid.at(x).at(y)->getOccupant();
	}else {
		throw -1;
	}
}
void Board::setPieceAt(int x, int y, Piece* p) {
	try {
		Piece* ahh = getPieceAt(x, y); if (ahh) { numPcs--;  }
		delete ahh; 
		grid.at(x).at(y)->setOccupant(p); if (p) { numPcs++; }
	}catch (int err) {
		// OOB
	}
	
}



void Board::writePieces(std::string fileName) {

	std::fstream fileTest;
	fileTest.open(fileName, std::ios::out | std::ios::binary | std::ios::app);
	
	fileTest.write((char*)&numPcs, sizeof(int));
	
	for (int x = 0; x < getWidth(); x++) {
		for (int y = 0; y < getHeight(); y++) {
			Piece* p = grid.at(x).at(y)->getOccupant();
			if (p) {
				bool w = p->isWhite();
				int t = p->getPieceType();
				fileTest.write((char*)&w, sizeof(bool));
				fileTest.write((char*)&t, sizeof(int));
				fileTest.write((char*)&x, sizeof(int));
				fileTest.write((char*)&y, sizeof(int));
			}
		}
	}

	fileTest.close();

}