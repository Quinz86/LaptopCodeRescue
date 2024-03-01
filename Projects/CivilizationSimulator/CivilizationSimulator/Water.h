#pragma once
#include "Block.h"
#include "SDL.h"

class Water : public Block {
public:
	Water();
	SDL_Texture* getSprite();

	static void setSprt(SDL_Texture* s);
private:
	static SDL_Texture* sprt;

};