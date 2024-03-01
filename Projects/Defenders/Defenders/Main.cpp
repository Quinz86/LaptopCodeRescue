#include "SDL.h"
#include <utility>
#include <time.h>
#include <thread>
#include <chrono>

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));


	SDL_Window *MAINscreen = SDL_CreateWindow("test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		700, 700,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	SDL_SetRenderDrawColor(MAINrenderer, 0, 0, 100, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);

	std::this_thread::sleep_for(std::chrono::seconds(5));


	// game code eventually goes here
	Game g = new Game(MAINrenderer);
	g.run();

	SDL_DestroyRenderer(MAINrenderer);
	SDL_DestroyWindow(MAINscreen);
	SDL_Quit();

	return 0;
}