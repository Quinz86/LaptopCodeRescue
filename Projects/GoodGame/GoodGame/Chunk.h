#pragma once

#include "Renderable.h"
#include "Updatable.h"

#define TILE_DIM 32
#define CHUNK_DIM 16

class Chunk : public Renderable, public Updatable{
public:
	Chunk(int x, int y);
	~Chunk();

	void render(SDL_Renderer* r);
	void update();
	int getFootPos();

	SDL_Rect* getRect(); //used internally

	static void setup(SDL_Texture* tt);
private:
	static SDL_Texture* tileTex;

	SDL_Rect rectan;

	bool grid[CHUNK_DIM][CHUNK_DIM];
};