#pragma once
#include <vector>
#include <string>

class Square;
class Piece;

class Board {
public:
	Board();
	Board(int w, int h);
	~Board();

	int getWidth();
	int getHeight();
	Piece* getPieceAt(int x, int y);
	void setPieceAt(int x, int y, Piece* p);

	void writePieces(std::string fileName);
private:
	std::vector<std::vector<Square*>> grid;
	int numPcs;
};