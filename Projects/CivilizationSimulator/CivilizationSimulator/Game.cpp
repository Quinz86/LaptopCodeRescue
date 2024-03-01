#include "Game.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "AI.h"
#include "Chunk.h"
#include "Block.h"

#include "Land.h"
#include "Water.h"
#include "Mountain.h"

#include "Useful.h"

//constructor
Game::Game(SDL_Renderer* rn) {
	r = rn;
}

void Game::run() {
	setup();

	bool done = false;
	SDL_Event event;
	//SDL_Rect letterDraw = { 0,0,25,25 };
	//SDL_Rect letterTrace = { 0,0,25,25 };
	std::string letterList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.!?- :";   //unneeded?
	//std::string message;
	Chunk* ctest = new Chunk(r);


	while (!done) {//begin gameloop
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_LEFT:  focusVelocity.x += -1; break;
					case SDLK_RIGHT:  focusVelocity.x += 1; break;
					case SDLK_DOWN:  focusVelocity.y += 1; break;
					case SDLK_UP:  focusVelocity.y += -1; break;
					case SDLK_ESCAPE: done = true; break;
					case SDLK_SPACE:	break;
					};
				}; break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:  focusVelocity.x += 1; break;
				case SDLK_RIGHT:  focusVelocity.x += -1; break;
				case SDLK_DOWN:  focusVelocity.y += -1; break;
				case SDLK_UP:  focusVelocity.y += 1; break;
				}; break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y }; break;
			case SDL_MOUSEBUTTONDOWN:
				AIs.push_back(new AI(r,mouseLocation.x,mouseLocation.y)); break;
			};
		};

		//screen stuff
		focus.x += focusVelocity.x;
		focus.y += focusVelocity.y;

		//updates		
		for (int x = 0; x < AIs.size(); x++) {
			AIs.at(x)->update();
		}

		//blits
		ctest->drawBlocks(0-focus.x,0-focus.y);
		for (int x = 0; x < AIs.size(); x++) {
			SDL_RenderCopy(r, AIs.at(x)->getSprite(), NULL, AIs.at(x)->getRectan());   //first null for all of original img
		}
		


		SDL_RenderPresent(r);
		SDL_Delay(5);
	};//end gameloop 

	///save here ///=====================s
	//actually saving the AI files in the ai destructor
	delete ctest;
	cleanup();
};

//setup and cleanup
void Game::setup() {

	//this isnt working
	std::string dir = "AIs/";
	for (auto & p : std::experimental::filesystem::directory_iterator(dir)){
		std::string path = p.path().filename().string();
		AIs.push_back(new AI( dir + path,  r));
	}

	Water::setSprt(getColorTexture(r, { 16,16,64 }));
	Land::setSprt(getColorTexture(r, { 128,128,128 }));
	Mountain::setSprt(getColorTexture(r, { 32,32,32 }));

	
}
void Game::cleanup() {
	//consider deleting AIs here, prepare for unload and reload fxns involving menu???
	for (int x = 0; x < AIs.size(); x++) {
		delete AIs.at(x);
	}
}