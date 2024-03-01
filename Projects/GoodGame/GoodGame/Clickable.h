#pragma once
#include "SDL.h"

class Clickable {
public:
	Clickable();
	~Clickable();

	virtual int click(SDL_Point* point) = 0;
	virtual SDL_Rect* getClickBox() = 0;
private:

};