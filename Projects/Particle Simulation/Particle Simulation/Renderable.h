#pragma once
#include "SDL.h"
#include "SDL_image.h"


class Renderable {
public:
	Renderable(int x, int y, int w, int h);
	Renderable(int x, int y, int w, int h, int xd, int yd);
	~Renderable();

	virtual void render(SDL_Renderer* r) = 0;
	SDL_Rect* getRect();

	void move(int x, int y);
private:
	SDL_Rect rectan;

	int xpos;
	int ypos;
	int width;
	int height;

	int xDisplacement;
	int yDisplacement;

	void updateRectan();
};