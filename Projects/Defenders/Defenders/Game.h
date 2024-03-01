#pragma once
#include "SDL.h"
#include <vector>
#include "Player.h"


class Game {
public:
	Game(SDL_Renderer* nr);
	void run();
private:
	SDL_Renderer* r;
	std::vector<Player*> players;

	int mode0();
	int mode1();
	int mode2();
};