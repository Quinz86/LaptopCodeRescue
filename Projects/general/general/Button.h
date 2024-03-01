#pragma once

#include "SDL.h"

class Button {
public:
	Button(int xn, int yn, int wn, int hn, int cv);
	~Button();

	int getClickValue();
	SDL_Rect getClickableArea();
private:
	SDL_Rect clickableArea;
	int clickValue;
};