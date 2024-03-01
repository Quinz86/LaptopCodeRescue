#pragma once
#include "SDL.h"
#include "living.h"
#include <string>
#include <vector>
#include "Planet.h"
#include "PolarStuff.h"


class Game {
public:
	Game(SDL_Renderer* nr, int screenW, int screenH);
	void run();
private:
	SDL_Renderer* r;
	SDL_Point mouseLocation;
	std::vector<Living*> players;
	std::vector<Planet*> planets;
	int currentPlanet = 0;
	PolarCoords focus;
	SDL_Point resolution;
	SDL_Texture* solid;
	SDL_Rect blitRect = { 0,0,4,96 };
};