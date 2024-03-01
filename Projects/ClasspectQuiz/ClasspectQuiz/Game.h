#pragma once

#include "SDL.h"
#include <vector>
#include "button.h"
#include "useful.h"


class Game {
public:
	Game(SDL_Renderer* mr);
	void run();
	void setup();
	void cleanup();
private:
	SDL_Renderer* r;
	SDL_Point mouseLocation;
	std::vector<SDL_Texture*> textures;
	std::vector<Button*> buttons;
	int selected;
	int clicked;
	std::vector<question> questions;
	int currentQuestionNum;

	//sburbStuff
	int classpects[12][12];
};