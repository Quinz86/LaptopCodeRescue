#pragma once
#include "SDL.h"

class entity {
public:
	entity();
	~entity();
protected:
	SDL_Point loc;
};