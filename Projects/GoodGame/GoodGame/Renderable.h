#pragma once
#include "SDL.h"
#include "SDL_image.h"


class Renderable {
public:
	Renderable();
	~Renderable();

	virtual void render(SDL_Renderer* r) = 0;

	static bool compHeights(Renderable* r1, Renderable* r2);
	virtual int getFootPos() = 0;
private:
};