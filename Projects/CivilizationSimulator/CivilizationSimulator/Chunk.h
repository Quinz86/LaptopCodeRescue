#pragma once
#include <vector>
#include "SDL.h"

#define XWID 32
#define YHGT 32
#define BSZ 32

class Block;
class Chunk {
public:
	Chunk(SDL_Renderer* nr);

	Block* getBlockAt(int x, int y);
	void drawBlocks(int Xpixel, int Ypixel);

	
protected:
private:
	SDL_Renderer* r;
	Block* grid[XWID][YHGT];

};