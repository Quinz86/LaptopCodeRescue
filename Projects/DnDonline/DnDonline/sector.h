#pragma once
#include <vector>
#include "entity.h"
#include "SDL.h"
#include "tile.h"

class sector {
public:
	sector(int x, int y);
	~sector();
private:
	std::vector<entity*> entities;
	SDL_Point worldLoc;
	std::vector<std::vector<tile>> map;
};