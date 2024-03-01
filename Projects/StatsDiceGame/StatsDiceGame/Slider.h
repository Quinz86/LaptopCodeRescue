#pragma once
#include <string>
#include "Renderable.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Clickable.h"


class Slider : public Clickable,public Renderable {
public:
	Slider(int x, int y, int w, int h, int m);
	~Slider();

	void render(SDL_Renderer* r);
	int click(SDL_Point* point);
	SDL_Rect* getClickBox();

	int getValue();
	void setMax(int m);

	static void setup();
private:
	static SDL_Texture* Ssprite;
	static SDL_Texture* Csprite;

	SDL_Rect clickerRectan = {};
	double clickerPos = 0;

	int max;
	int min = 100;
};