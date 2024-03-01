#pragma once
#include "SDL.h"
#include <vector>
//#include "Thing.h"  this breaks the cycle, see line 7


class Thing;
class Player;
class Background;
class Tile;
class Button;
class Game {
public:
	Game(SDL_Renderer* rn, int w, int h);
	~Game();
	void run();
	void save();
	
	SDL_Point getMouseLocation();
	SDL_Point getFocus();
	SDL_Rect realignRectangle(SDL_Rect toRealign);
	SDL_Renderer* getRenderer();
private:
	std::vector<Background*> backgrounds;
	std::vector<Tile*> tiles;
	std::vector<Thing*> things;
	Player* mainCharacter;
	std::vector<Background*> gui;
	std::vector<Button*> buttons;

	bool done;
	int gamemode;

	SDL_Point mouseLocation;
	SDL_Point focus;
	SDL_Point focusVelocity;
	SDL_Point dimensions;
	SDL_Renderer* r;
	
	void display();
	
};