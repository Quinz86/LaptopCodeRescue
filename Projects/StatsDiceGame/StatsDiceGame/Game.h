#pragma once
#include "SDL.h"
#include <vector>
#include "DiceSet.h"

class Renderable;
class Clickable;
class Updatable;

class Game {
public:
	Game(int sW, int sH, SDL_Renderer* r);
	~Game();

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

	DiceSet* bankSet;
	DiceSet* playerSet;
	
	int playerMoney = 10000;
	bool ok = true;
	int playerBet = 100;
	bool addedADie = false;

	void respondToClickNum(int n);
	void replacePlayerSet(int newNumDice);
	void replaceBankSet(int newNumDice);
};