#pragma once
#include "SDL.h"
#include "string"

struct tile {
	std::string name;
	SDL_Texture* sprite;
	bool traversable;
	bool projectile_transparent;
	bool selectable;
};