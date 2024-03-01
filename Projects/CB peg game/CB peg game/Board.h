#pragma once

#include "Move.h"
#include <vector>
#include <string>

class Board {
public:
	Board();
	Board(Board* other);
	~Board();

	bool getPegAt(int l, int n);
	void setPegAt(int l, int n, bool b);
	std::vector<Move>* getPreviousMoves();
	void addMove(Move m);
	int getNumPegsLeft();

	std::string toString();

	static int getNthTriangularNumber(int s);
	static int decodeLNtoP(int l, int n);
	static int decodePtoLN(int p); //dont use
private:
	
	
	std::vector<Move> previousMoves = std::vector<Move>();

	//regular
	
	bool grid[15] = {   false,
						true, true,
						true, true, true,
						true, true, true, true,
						true, true, true, true, true  };
	
	//testing
	/*
	bool grid[15] = {   false,
						false, false,
						true, true, false,
						false, false, true, false,
						false, false, false, false, false };
	*/
};