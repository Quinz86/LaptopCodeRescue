#pragma once




struct Peg {

	bool active;
	bool color; // true = red, false = black;
	unsigned char connections;

	bool counted;

	void setConnection(unsigned char other, bool onOff);
	bool getConnection(unsigned char other);
};