#pragma once
#include "SDL.h"


inline SDL_Texture* getColorTexture(SDL_Renderer* rend, SDL_Color c) {
	SDL_Texture* t;
	SDL_Surface* s = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0); //the 2s can probably be 1s
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, c.r, c.g, c.b));
	t = SDL_CreateTextureFromSurface(rend, s);
	SDL_FreeSurface(s);
	return t;
};