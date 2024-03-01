#pragma once

#include "Peg.h"
#include "SDL.h"

struct Board {
	Peg grid[24][24];


	void addPeg(SDL_Point pt, bool c); // true = red, false = black;
	void removePeg(SDL_Point pt);

	void removeConnection(SDL_Point pt1, SDL_Point pt2);
	void createConnection(SDL_Point pt1, SDL_Point pt2);
	bool flipConnection(SDL_Point pt1, SDL_Point pt2);

	void wipeCounted();
	bool isBlocked(SDL_Point pt1, SDL_Point pt2);

	static bool pointIsInBounds(SDL_Point pt);

private:
	unsigned char getDirectionFromPoint(SDL_Point source, SDL_Point other);
	SDL_Point getPointFromDirection(SDL_Point source, unsigned char conDir);
};