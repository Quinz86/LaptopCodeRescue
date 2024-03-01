


#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include <time.h>   //time(), for srand() seed

//#include <utility>   
//#include <string>
//#include "filesystem"
//#include <thread>





int main(int argc, char ** argv) {

	//====== SETUP THE VISUALS==========
	SDL_Init(SDL_INIT_VIDEO);//??
	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));

	SDL_Window *MAINscreen = SDL_CreateWindow("SDL_Template",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		500, 500,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 128, 128, 128, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);
	//====== \SETUP THE VISUALS==========







	SDL_DestroyRenderer(MAINrenderer);
	SDL_DestroyWindow(MAINscreen);
	SDL_Quit();
	return 0;
}













