#pragma once
#include "SDL.h"
#include <vector>

class AI;
class Chunk;

class Game {
public:
	Game(SDL_Renderer* rn);
	void setup();
	void cleanup();
	void run();


private:
	SDL_Renderer* r;
	std::vector<AI*> AIs;
	//std::vector<std::vector<Chunk*>> map;
	SDL_Point mouseLocation;
	SDL_Point focus;
	SDL_Point focusVelocity;
};