#pragma once
#include "Block.h"
#include "SDL.h"

class Mountain : public Block {
public:
	Mountain();
	SDL_Texture* getSprite();

	static void setSprt(SDL_Texture* s);
private:
	static SDL_Texture* sprt;

};