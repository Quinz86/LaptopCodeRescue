#pragma once

#include "Thing.h"

class Tile : public Thing {
public:
	Tile(int xn, int ny, int wn, int hn, int matStart);
	~Tile();

	void blit_self(); 
	void upd8();
	void resize(int wn, int hn);

	static void setMaterials(int x, SDL_Texture* spr);
private:
	int myMaterial;

	static SDL_Texture* materials[3];
};