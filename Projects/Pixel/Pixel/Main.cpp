#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "filesystem"
#include <iostream>
#include <queue>
#include <math.h>



#define F0 0
#define F1 (1.0/7)
#define F2 (2.0/7)
#define F3 (3.0/7)
#define F4 (4.0/7)
#define F5 (5.0/7)
#define F6 (6.0/7)
#define F7 1
void getColor(double fraction, SDL_Renderer* r) {
	if (fraction < F1) {
		SDL_SetRenderDrawColor(r,
			255,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255);
	}
	else if (fraction < F2) {
		fraction -= F1;
		SDL_SetRenderDrawColor(r,
			255,
			((Uint8)floor(255 * (fraction / F1))),
			0,
			255);
	}
	else if (fraction < F3) {
		fraction -= F2;
		SDL_SetRenderDrawColor(r,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255,
			0,
			255);
	}
	else if (fraction < F4) {
		fraction -= F3;
		SDL_SetRenderDrawColor(r,
			0,
			255,
			((Uint8)floor(255 * (fraction / F1))),
			255);
	}
	else if (fraction < F5) {
		fraction -= F4;
		SDL_SetRenderDrawColor(r,
			0,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255,
			255);
	}
	else if (fraction < F6) {
		fraction -= F5;
		SDL_SetRenderDrawColor(r,
			((Uint8)floor(255 * (fraction / F1))),
			0,
			255,
			255);
	}
	else if (fraction < F7) {	// fraction < F7
		fraction -= F6;
		SDL_SetRenderDrawColor(r,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			0,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255);
	}
	else {
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	}
}



#define W 700
#define H 700

int main(int argc, char ** argv)
{
	

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



	
	int numStarters = 1;
	int highest = 0;
	short grid[W][H];
	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			grid[x][y] = -1;
		}
	}
	std::queue<SDL_Point> spotNext = std::queue<SDL_Point>();
	
	//setup starters and queueu
	for (int i = 0; i < numStarters; i++) {
		int xs = rand() % W;
		int ys = rand() % H;
		grid[xs][ys] = 0;
		spotNext.push({xs,ys});
		std::cout << xs << "," << ys << std::endl;
	}
	
	//handle the queueu
	while (!spotNext.empty()) {
		SDL_Point spot = spotNext.front();
		
		for (int xn = -1; xn <= 1; xn += 2) {
			SDL_Point next = { spot.x + xn,spot.y };
			if (next.x >= 0 && next.x < W && next.y >= 0 && next.y < H && grid[next.x][next.y] == -1) {
				short val = grid[spot.x][spot.y] + 1;
				grid[next.x][next.y] = val;
				spotNext.push(next);
				if (val > highest) { highest = val; }
			}
		}
		for (int yn = -1; yn <= 1; yn += 2) {
			SDL_Point next = { spot.x,spot.y + yn };
			if (next.x >= 0 && next.x < W && next.y >= 0 && next.y < H && grid[next.x][next.y] == -1) {
				short val = grid[spot.x][spot.y] + 1;
				grid[next.x][next.y] = val;
				spotNext.push(next);
				if (val > highest) { highest = val; }
			}
		}
		spotNext.pop();
	}

	//done, now blit
	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			if ( grid[x][y]  == 0) {
				SDL_SetRenderDrawColor(MAINrenderer, 255, 255, 255, 255);
				
			}else {
				getColor(grid[x][y]/(double)highest,MAINrenderer);
			}
			SDL_RenderDrawPoint(MAINrenderer,x,y);
		}
	}
	SDL_RenderPresent(MAINrenderer);

	

	SDL_Event event;
	//begin game loop
	bool done = false;
	while (!done) {

		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			}
		}
	}
	
	SDL_DestroyRenderer(MAINrenderer);
	SDL_DestroyWindow(MAINscreen);
	SDL_Quit();

	return 0;
}

