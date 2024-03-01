#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "filesystem"
#include <iostream>


#include "TextureManager.h"
#include "Game.h"
#include "Button.h"
#include "Die.h"
#include "WordBox.h"
#include "Slider.h"



int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);//??

	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));


	SDL_Window *MAINscreen = SDL_CreateWindow("GENERAL",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		1300, 700,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 100, 100, 100, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);


	//setup here
	//we usin' a texturemanager now


	// game code eventually goes here
	int w, h;
	SDL_GetWindowSize(MAINscreen, &w, &h);


	//setups
	TextureManager::setUp(MAINrenderer);
	Game::setup(MAINrenderer);
	Button::setUp();
	Die::setup();// this is doing something now, its populating the dice vectors
	WordBox::setUp();
	Slider::setup();

	//========= RUN THE GAME==============
	Game myGame = Game(w,h,MAINrenderer);
	myGame.run();
	//====================================



	//cleanups
	TextureManager::cleanUp();

	SDL_Quit();

	return 0;
}

