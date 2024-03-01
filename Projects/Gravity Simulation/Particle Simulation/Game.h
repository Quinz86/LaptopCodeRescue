#pragma once
#include "SDL.h"
#include <vector>

class Renderable;
class Clickable;
class Updatable;

class Particle;

class Game {
public:
	Game(int sW, int sH, SDL_Renderer* r);
	~Game();

	int getScreenWidth();
	int getScreenHeight();
	std::vector<Particle*>* getParticleListPointer();

	void resetWithXParticles(int x);


	static void setup(SDL_Renderer* r);
	void run();
private:
	SDL_Renderer* rend;
	bool done = false;
	int screenWidth;
	int screenHeight;
	std::vector<Renderable*> toRender = std::vector<Renderable*>();
	std::vector<Clickable*> toClick = std::vector<Clickable*>();
	std::vector<Updatable*> toUpdate = std::vector<Updatable*>();
	SDL_Point mouseLocation = {0,0};

	
	std::vector<Particle*> particleList = std::vector<Particle*>();

	void respondToClickNum(int n);
};