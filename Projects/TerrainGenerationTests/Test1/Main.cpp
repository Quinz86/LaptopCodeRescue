#include <iostream>
#include <noise/noise.h>
#include <time.h>
#include <thread>
#include <chrono>

#include "ColorGradient.h"


#define W 400
#define H 400

int main(int argc, char** argv) {


	SDL_Init(SDL_INIT_VIDEO);//??
	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));
	SDL_Window *MAINscreen = SDL_CreateWindow("GENERAL",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		W, H,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 0, 0, 0, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);

	int w, h;
	SDL_GetWindowSize(MAINscreen, &w, &h);
	//end SDL setup


	double z = rand()*100;
	const short highest = 200;
	const short lowest = highest * -1;
	noise::module::Perlin myModule;

	//begin game loop
	SDL_Event event;
	bool done = false;
	while (!done) {
		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			}
		}
		//end event handling

		z += 0.01;

		//begin blit
		for (int x = 0; x < W; x++) {
			for (int y = 0; y < H; y++) {
				getColor(((short)(myModule.GetValue(x / 100.0, y / 100.0, z) * 100) - lowest) / (double)(highest - lowest), MAINrenderer);

				SDL_RenderDrawPoint(MAINrenderer, x, y);
			}
		}
		SDL_RenderPresent(MAINrenderer);
		//end blit

	}
	//end game loop

	SDL_DestroyRenderer(MAINrenderer);
	SDL_DestroyWindow(MAINscreen);
	SDL_Quit();


	return 0;
}