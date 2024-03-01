#include "SDL.h"
#include "Game.h"
#include <utility>   //do i need this???, yes
#include <time.h>

//global variable game??
Game myGame;
Game* getGame() {
	return &myGame;
}

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));


	SDL_Window *MAINscreen = SDL_CreateWindow("MineTheMoon",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		1300, 700,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	SDL_SetRenderDrawColor(MAINrenderer, 100, 0, 0, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);

	int w, h;
	SDL_GetWindowSize(MAINscreen, &w, &h);
	// game code eventually goes here
	myGame = Game(MAINrenderer,w,h);
	myGame.run();

	SDL_Quit();

	return 0;
}

