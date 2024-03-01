#pragma once

class Piece;

class Square {
public:
	Square();
	~Square();

	Piece* getOccupant();
	void setOccupant(Piece* p);
private:
	Piece* occupant;
};