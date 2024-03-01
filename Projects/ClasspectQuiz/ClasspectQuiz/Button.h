#pragma once
#include "SDL.h"

class Button {
public:
	Button(SDL_Rect* rectan, int val);

	int click();
	SDL_Rect* getRectan();
private:
	int value;
	SDL_Rect* rectan;
};