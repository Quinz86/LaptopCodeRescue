#include "Game.h"
//#include "winsock.h"
#include <iostream>
#include "SDL_image.h"
#include <math.h>
#define CAMERA_DISTANCE 5


//constructor
Game::Game(SDL_Renderer* nr, int screenW, int screenH) {
	r = nr;
	resolution = { screenW, screenH };

	SDL_Surface* surf;
	surf = IMG_Load("sprites/stone_01.png");
	solid = SDL_CreateTextureFromSurface(r, surf);
	//players.push_back(new Living(50,50,50,50, textu));
	//===
	SDL_FreeSurface(surf);

	//planets.push_back(new Planet());
	focus = { 25,0.1 };
	

}

void Game::run() {
	bool done = false;
	SDL_Event event;

	while (!done) {//begin gameloop
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_LEFT:  focus.theta += deltaTheta(focus.r, CAMERA_DISTANCE); break;
					case SDLK_RIGHT:  focus.theta -= deltaTheta(focus.r, CAMERA_DISTANCE); break;
					case SDLK_DOWN: focus.r -= CAMERA_DISTANCE; break;
					case SDLK_UP:  focus.r += CAMERA_DISTANCE; break;
					case SDLK_ESCAPE: done = true; break;
					case SDLK_SPACE:	break;
					};
				};
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:  break;
				case SDLK_RIGHT:  break;
				case SDLK_DOWN:  break;
				case SDLK_UP: break;
				};
				break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y };
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			};
		};

		//SDL_RenderCopy(r, textures[3], NULL, buttons[5]->getRectan()); //i dont know why this is here, just add it to the bg texture
	
		/*for (int p = 0; p < players.size(); p++) {
			SDL_RenderCopy(r, players.at(p)->getSprite(), NULL, players.at(p)->getRectan() );
		}*/
	
		/*
				|		
				|			__y__
				|			|	|
		-------------------x|-r-|
				|			|___|
				|
				|
		*/
		double startTheta = (atan2(0+resolution.x, focus.r - resolution.y)); //y, then x   
		double endTheta = (atan2(0-resolution.x, focus.r - resolution.y));  //y, x, this needs to be mod 2PI
		//start and end theta should be the same

		for (int l = (focus.r - resolution.y/2) / 96; l < (focus.r + resolution.y/2) / 96; l++) {
			if (l < 0) { l = 0; };
			for (double t = focus.theta + startTheta; t < endTheta; t += deltaTheta((l*96)+(96/2),4)) {
				blitRect.x = ;
				blitRect.y = ;
				SDL_RenderCopyEx(r, solid, NULL, &blitRect, (focus.theta - t)*(180.0/M_PI), NULL, SDL_FLIP_NONE);
			}
		}

		SDL_RenderPresent(r);
		SDL_Delay(5);
	}//end gameloop

}