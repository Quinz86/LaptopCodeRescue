#pragma once
#include "SDL.h"

class Clickable {
public:
	Clickable();
	~Clickable();

	virtual int click() = 0;
	virtual SDL_Rect* getClickBox() = 0;
private:

};