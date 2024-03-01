#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "filesystem"
#include <iostream>

#define PADDLE_SPEED 0.5

#define PADDLE_WIDTH 30
#define PADDLE_HEIGHT 150

#define BALL_X_SPEED 1

#define BALL_DIM 30

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);//??

	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));
	
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Screen_Width = DM.w;
	auto Screen_Height = DM.h;

	//===============================================================
	SDL_Window *USERpaddle = SDL_CreateWindow("Player",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		PADDLE_WIDTH, PADDLE_HEIGHT,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *UR = SDL_CreateRenderer(USERpaddle, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(UR, 220, 220, 220, 255);
	SDL_RenderClear(UR);
	SDL_RenderPresent(UR);
	//===============================================================
	SDL_Window *CPUpaddle = SDL_CreateWindow("Enemy",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		PADDLE_WIDTH, PADDLE_HEIGHT,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL	
	);
	SDL_Renderer *CR = SDL_CreateRenderer(USERpaddle, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(CR, 220, 220, 220, 255);
	SDL_RenderClear(CR);
	SDL_RenderPresent(CR);
	///===============================================================
	SDL_Window *BALL = SDL_CreateWindow("Ball",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		BALL_DIM, BALL_DIM,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *BR = SDL_CreateRenderer(USERpaddle, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(BR, 220, 220, 220, 255);
	SDL_RenderClear(BR);
	SDL_RenderPresent(BR);
	//===================================================================

	//setup here

	// game code eventually goes here
	


	//setups
	double xpos_u = 0.0;
	double ypos_u = 0.0;
	double xvel_u = 0.0;
	double yvel_u = 0.0;

	double xpos_c = 0.0;
	double ypos_c = 0.0;
	double xvel_c = 0.0;
	double yvel_c = 0.0;

	double xpos_b = 0.0;
	double ypos_b = 0.0;

	//========= RUN THE GAME==============
	bool done = false;
	SDL_Event event;
	//begin game loop
	while (!done) {
		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: done = true; break;
					case SDLK_UP: yvel_u += -PADDLE_SPEED; break;
					case SDLK_DOWN: yvel_u += PADDLE_SPEED;  break;
					case SDLK_RIGHT: xvel_u += PADDLE_SPEED; break;
					case SDLK_LEFT:  xvel_u += -PADDLE_SPEED;  break;
					}
				}; break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_UP:  yvel_u -= -PADDLE_SPEED;  break;
				case SDLK_DOWN: yvel_u -= PADDLE_SPEED; break;
				case SDLK_RIGHT: xvel_u -= PADDLE_SPEED; break;
				case SDLK_LEFT:  xvel_u -= -PADDLE_SPEED; break;
				}
				break;


			}
		}

		//begin updating
		xpos_u += xvel_u;
		ypos_u += yvel_u;
		if (xpos_u < 0) { xpos_u = 0; }
		if (xpos_u > Screen_Width - PADDLE_WIDTH) { xpos_u = Screen_Width - PADDLE_WIDTH; }
		if (ypos_u < 0) { ypos_u = 0; }
		if (ypos_u > Screen_Height - PADDLE_HEIGHT) { ypos_u = Screen_Height - PADDLE_HEIGHT; }

		SDL_SetWindowPosition(USERpaddle,(int)xpos_u,(int)ypos_u);
		
		//begin drawing
		SDL_RenderClear(UR);
		SDL_RenderClear(CR);
		SDL_RenderClear(BR);
		/*
		for (int x = 0; x < toRender.size(); x++) {
			toRender.at(x)->render(rend);
		}
		*/
		SDL_RenderPresent(UR);
		SDL_RenderPresent(CR);
		SDL_RenderPresent(BR);
	}
	//====================================



	//cleanups

	SDL_Quit();

	return 0;
}

