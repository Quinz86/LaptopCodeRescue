#include "Chunk.h"
#include "Game.h"

//static 
SDL_Texture* Chunk::tileTex = nullptr;

void Chunk::setup(SDL_Texture* tt) {
	tileTex = tt;
}






//constructors
Chunk::Chunk(int x, int y) : Renderable(), Updatable() {
	//fill it with trues
	for (int xq = 0; xq < CHUNK_DIM; xq++) {
		for (int yq = 0; yq < CHUNK_DIM; yq++) {
			grid[xq][yq] = true;
		}
	}
	rectan = {x,y,TILE_DIM*CHUNK_DIM,TILE_DIM*CHUNK_DIM};
}
Chunk::~Chunk() {

}




//big 3 inherited
void Chunk::render(SDL_Renderer* r) {
	
	for (int xq = 0; xq < CHUNK_DIM; xq++) {
		for (int yq = 0; yq < CHUNK_DIM; yq++) {
			SDL_Rect tmepRcet = { getRect()->x + xq*TILE_DIM - Game::getScreenLocation()->x,
								  getRect()->y + yq*TILE_DIM - Game::getScreenLocation()->y,
								  TILE_DIM, 
								  TILE_DIM };
			SDL_RenderCopy(r, tileTex, NULL, &tmepRcet);
		}
	}
	
}
void Chunk::update() {

}
int Chunk::getFootPos() {
	return getRect()->y; //top of rect, not bottom
}


//methods
SDL_Rect* Chunk::getRect() {
	return &rectan;
}


