#pragma once
#include <vector>
#include "SDL.h"

class Button;
class Game;

class Menu {
public:
	Menu();
	~Menu();

	void addButton(Button* b);
	void virtual draw(SDL_Renderer* r);

	void virtual click(SDL_Point* p);
	void mouseMoved(SDL_Point* p);

	static void setup(Game* gn, SDL_Texture* backG, SDL_Texture* transpBlue, SDL_Renderer* r);

protected:
	static Game* g;
	static SDL_Texture* bg;
	static SDL_Texture* blueTransparent;
	static SDL_Texture* greySolid;

private:
	std::vector<Button*> buttons;
};