#pragma once
#include "SDL.h"
#include <vector>
#include "sector.h"
#include "player.h"

class Game {
public:
	Game(SDL_Renderer* nr, int w, int h);
	~Game();
	void run();
private:
	SDL_Renderer* r;
	SDL_Point resolution;
	std::vector<sector*> sectors;
	std::vector<player*> players;
	SDL_Point mouseLocation;
	SDL_Point focus;
};