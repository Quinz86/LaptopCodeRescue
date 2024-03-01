#include "SDL.h"
#include "SDL_image.h"
#include <random>
#include <utility>
#include <time.h>

#include "Game.h"




int main(int argc, char ** argv) {
	SDL_Init(SDL_INIT_VIDEO);//??

	SDL_Init(SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);
	srand(time(NULL));


	



	//RUN THE GAME==========================
	Game::setup();
	Game::run();
	Game::cleanup();
	//RUN THE GAME==========================


	SDL_Quit();
	return 0;
}