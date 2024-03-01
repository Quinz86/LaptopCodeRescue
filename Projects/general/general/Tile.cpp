#include "Tile.h"

//statics
SDL_Texture* Tile::materials[3]; // = { nullptr,nullptr,nullptr };
void Tile::setMaterials(int x, SDL_Texture* spr) {
	materials[x] = spr;
}

//constructors
Tile::Tile(int xn, int yn, int wn, int hn, int matStart):Thing(xn, yn, wn, hn, false) {
	myMaterial = matStart;
}
Tile::~Tile() {

}

//other
void Tile::resize(int wn, int hn){
	rectan.w = wn;
	rectan.h = hn;
}


//virtual
void Tile::upd8() {

}
void Tile::blit_self() {
	//the bane of my existance ----- is right here
	SDL_RenderCopy(g->getRenderer(),materials[myMaterial],NULL, &g->realignRectangle(getRectan()));
}