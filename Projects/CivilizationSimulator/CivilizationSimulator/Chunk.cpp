#include "Chunk.h"
#include "Block.h"

#include "Land.h"
#include "Water.h"
#include "Mountain.h"
//statics


//constructor
Chunk::Chunk(SDL_Renderer* nr) {
	r = nr;

	for (int x = 0; x < XWID; x++) {
		for (int y = 0; y < YHGT; y++) {
			switch (rand() % 0x03 ) {
			case 0: grid[x][y] = new Land(); break;
			case 1: grid[x][y] = new Water(); break;
			case 2: grid[x][y] = new Mountain(); break;
			}
		}
	}
}

Block* Chunk::getBlockAt(int x, int y) {
	return grid[x][y];
}
void Chunk::drawBlocks(int Xpixel, int Ypixel) {
	SDL_Rect tempRect = {Xpixel, Ypixel, BSZ,BSZ};
	for (int x = 0; x < XWID; x++) {
		for (int y = 0; y < YHGT; y++){
			SDL_RenderCopy(r, getBlockAt(x,y)->getSprite(), NULL, &tempRect);
			
			tempRect.y += BSZ;
		}
		tempRect.x += BSZ;
		tempRect.y = Ypixel;
	}
}