#pragma once
#include "SDL.h"
#include <string>
#include <vector>

class Button;
class Menu;
class Board;

class Game {
public:
	Game(SDL_Renderer* rend);
	~Game();
	void run();

	void buttonReaction(int n, Button* from);

	static void setup(SDL_Texture* l, SDL_Texture* f);

	bool isSinglePlayer();
	void drawWords(SDL_Rect* wordBox, std::string words);
private:
	static std::string letterList;
	static SDL_Rect letterSelector;
	static SDL_Rect letterStamper;
	
	static SDL_Texture* logo;
	static SDL_Texture* font;
	
	static std::vector<Menu*> states;
	//maybe rework this =============
	static Button* nameMaker;
	static Button* fileChooser;
	//maybe rework this =============
	
	
	SDL_Renderer* r;
	SDL_Point mouseLocation;

	int gameState;
	bool done;
	bool singlePlayer;

	Button* typing;
	bool shift;

	


};