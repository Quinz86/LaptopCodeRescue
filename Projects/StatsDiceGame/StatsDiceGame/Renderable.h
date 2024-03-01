#pragma once
#include "SDL.h"
#include "SDL_image.h"


class Renderable {
public:
	Renderable(int x, int y, int w, int h);
	~Renderable();

	virtual void render(SDL_Renderer* r) = 0;
	SDL_Rect* getRect();
private:
	SDL_Rect rectan;
};