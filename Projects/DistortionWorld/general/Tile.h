#pragma once

#include "Thing.h"

class Tile : public Thing {
public:
	static const int TILE_WIDTH = 32;
	static const int TILE_HIGHT = 32;

	Tile(int xn, int ny, int wn, int hn, int matStart);
	~Tile();

	void blit_self(); 
	void resize(int wn, int hn);
	void upd8();

	static void setMaterials(int x, SDL_Texture* spr);
	static void setup();
private:
	int material;
	int orientation;

	static SDL_Texture* materials[3];
};