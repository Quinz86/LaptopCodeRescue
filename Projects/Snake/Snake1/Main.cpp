
#include <iostream>
#include <stdlib.h>
#include <stdio.h>




#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include <unordered_map> //do i need this?
#include <string>
#include <vector>

#define PIX_WH 16
#define BOARD_WH 32
#define MAX_DELAY 200 
#define MIN_DELAY 2

int main(int argc, char ** argv){

	//====== SETUP THE VISUALS==========
	SDL_Init(SDL_INIT_VIDEO);//??
	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));

	SDL_Window *MAINscreen = SDL_CreateWindow("Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		PIX_WH*BOARD_WH, PIX_WH*BOARD_WH,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 128, 128, 128, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);
	//====== \SETUP THE VISUALS==========


	//setups
	unsigned short grid[BOARD_WH][BOARD_WH];
	for (int x = 0; x < BOARD_WH; x++) {
		for (int y = 0; y < BOARD_WH; y++) {
			grid[x][y] = 0;
		}
	}
	unsigned short snakeLength = 3; //edit??
	SDL_Point snakeHead = { 16,16 };
	SDL_Point apple = {rand()%BOARD_WH,rand()%BOARD_WH};
	unsigned char dir = 0;
	unsigned char prevDir = 0;
	unsigned short currentDelay = MAX_DELAY - ((MAX_DELAY - MIN_DELAY) * ((double)snakeLength / (BOARD_WH*BOARD_WH)));
	unsigned short delayLeft = currentDelay;
	SDL_Rect stamper = { 0,0,PIX_WH,PIX_WH };

		

	//========= RUN THE GAME==============
	
	//begin game loop
	bool done = false;
	SDL_Event event;
	while (!done) {

		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: done = true; break;
					case SDLK_RIGHT: if (prevDir != 2) { dir = 0; } break;
					case SDLK_UP: if (prevDir != 3) { dir = 1; } break;
					case SDLK_LEFT: if (prevDir != 0) { dir = 2; } break;
					case SDLK_DOWN: if (prevDir != 1) { dir = 3; } break;
					};
				}
				break;
			}

		}
		//end event handling


		//====================================
		//updates
		delayLeft--;
		if (delayLeft <= 0) {
			switch (dir) {
			case 0: snakeHead.x++; break;
			case 1: snakeHead.y--; break;
			case 2: snakeHead.x--; break;
			case 3: snakeHead.y++; break;
			}
			if (grid[snakeHead.x][snakeHead.y] > 0 || snakeHead.x < 0 || snakeHead.x >= BOARD_WH || snakeHead.y < 0 || snakeHead.y >= BOARD_WH) {
				done = true; break;
			}

			if (snakeHead.x == apple.x && snakeHead.y == apple.y) {
				apple = { rand()%BOARD_WH,rand()%BOARD_WH };
				snakeLength++;
				currentDelay = MAX_DELAY - ((MAX_DELAY - MIN_DELAY) * ((double)snakeLength / (BOARD_WH*BOARD_WH)));
			}else {
				for (int x = 0; x < BOARD_WH; x++) {
					for (int y = 0; y < BOARD_WH; y++) {
						if (grid[x][y] > 0) {
							grid[x][y]--;
						}
					}
				}
			}
			delayLeft = currentDelay;
			grid[snakeHead.x][snakeHead.y] = snakeLength;
			prevDir = dir;
		}
	
		//====================================
		//render
		SDL_SetRenderDrawColor(MAINrenderer, 128, 128, 128, 255);
		SDL_RenderClear(MAINrenderer);

		SDL_SetRenderDrawColor(MAINrenderer, 255, 255, 255, 255);
		for (int x = 0; x < BOARD_WH; x++) {
			for (int y = 0; y < BOARD_WH; y++) {
				if (grid[x][y] > 0) {
					stamper.x = x*PIX_WH;
					stamper.y = y*PIX_WH;
					SDL_RenderFillRect(MAINrenderer, &stamper);
				}
			}
		}

		SDL_SetRenderDrawColor(MAINrenderer, 255, 0, 0, 255);
		stamper.x = apple.x*PIX_WH;
		stamper.y = apple.y*PIX_WH;
		SDL_RenderFillRect(MAINrenderer, &stamper);

		SDL_RenderPresent(MAINrenderer);
	}

	//cleanups

	//close
	SDL_Quit();
	return 0;
}