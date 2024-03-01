#pragma once
#include "Block.h"
#include "SDL.h"

class Land : public Block {
public:
	Land();
	SDL_Texture* getSprite();

	static void setSprt(SDL_Texture* s);
private:
	static SDL_Texture* sprt;

};