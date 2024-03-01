#pragma once
#include "SDL.h"
#include <string>

class Game;

class Button {
public:
	Button(int n, SDL_Rect rectan, std::string disp, bool c);
	void click(Game* g);
	SDL_Rect* getRect();

	void setDisplay(std::string d);
	std::string getDisplay();
	void setClickable(bool c);
	bool getCLickable();
	void setHighlighted(bool h);
	bool getHighlighted();

private:

	bool clickable;
	bool highlighted;
	int num;
	std::string display;
	SDL_Rect box;
};