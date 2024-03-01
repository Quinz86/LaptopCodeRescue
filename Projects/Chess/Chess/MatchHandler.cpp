#include "MatchHandler.h"
#include "Board.h"
#include "fstream"
#include "Piece.h"
#include "PieceType.h"
#include "AllThePieces.h"

//constructor
MatchHandler::MatchHandler(std::string fN, bool sP){
	fileName = fN;
	singlePlayer = sP;

	int wid, hgt;
	bool w;
	int np;

	std::fstream fileTest;
	fileTest.open(fileName, std::ios::in | std::ios::binary);
	fileTest.read((char*)&wid, sizeof(int));
	fileTest.read((char*)&hgt, sizeof(int));
	fileTest.read((char*)&w, sizeof(bool));
	fileTest.read((char*)&np, sizeof(int));

	whitesTurn = w;

	b = new Board(wid, hgt);

	bool c;
	PieceType t;
	int x, y;
	for (int p = 0; p < np; p++) {

		fileTest.read((char*)&c, sizeof(bool));
		fileTest.read((char*)&t, sizeof(int));
		fileTest.read((char*)&x, sizeof(int));
		fileTest.read((char*)&y, sizeof(int));

		switch (t){
		case KING: b->setPieceAt(x, y, new King(c)); break;
		case QUEEN: b->setPieceAt(x, y, new Queen(c)); break;
		case BISHOP: b->setPieceAt(x, y, new Bishop(c)); break;
		case KNIGHT: b->setPieceAt(x, y, new Knight(c)); break;
		case ROOK: b->setPieceAt(x, y, new Rook(c)); break;
		case PAWN: b->setPieceAt(x, y, new Pawn(c)); break;
		default: break;
		}
		
	}

	fileTest.close();
}



void MatchHandler::run(){

}

void MatchHandler::listen(SOCKET* s){

}