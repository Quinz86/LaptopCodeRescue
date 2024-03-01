#pragma once
#include "SDL.h"
#include "PolarStuff.h"

class Living {
public:
	Living(int nx, int ny, int nw, int nh ,SDL_Texture* nsprite);
	void update();
	SDL_Point getLoc();
	SDL_Texture* getSprite();
	SDL_Rect* getRectan();
private:
	PolarCoords loc;
	SDL_Point vel = { 0,0 };
	SDL_Rect rectan;
	SDL_Texture* sprite;
};