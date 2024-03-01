#include "Game.h"
#include "Thing.h"
#include "Player.h"
#include "Background.h"
#include "Tile.h"
#define SCROLLSPEED 1

//constructor
Game::Game(SDL_Renderer* rn, int w, int h) {
	r = rn;
	focus = { 500,400 };
	focusVelocity = { 0,0 };
	dimensions = { w,h };

	mouseLocation = { 0,0 }; //do i need this?

	done = false;
	gamemode = 0;

	//DONT PUSH BACK THINGS HERE, IT WILL FREAK OUT, well, i guess not?, but you shouldnt, im not sure, 
	//idk anymore, alot of things have changed, think about it later
	/*
	things.push_back(new Background("first.png",0,0,768,768));
	things.push_back(new Thing(50, 50, 50, 50));
	*/
	//DONT DO THIS ------^
}
Game::~Game() {
	//should probably delete everything in the things vector(s) here, learn how to do that 
	
	for (int x = 0; x < backgrounds.size(); x++) {
		delete backgrounds.at(x);
	}
	for (int x = 0; x < tiles.size(); x++) {
		delete tiles.at(x);
	}
	for (int x = 0; x < things.size(); x++) {
		delete things.at(x);
	}
	for (int x = 0; x < gui.size(); x++) {
		delete gui.at(x);
	}
	for (int x = 0; x < buttons.size(); x++) {
		delete buttons.at(x);
	}
}

void Game::run() {
	//backgrounds.push_back(new Background("step1.png", 0, 0, 1000, 600, false));
	tiles.push_back(new Tile(300,200,32,32,0));
	tiles.push_back(new Tile(400,200,32,32,1));
	things.push_back(new Player(-100,100));
	//=======================
	mainCharacter = new Player(0,0);
	things.push_back(mainCharacter);
	//=======================
	gui.push_back(new Background("topBanner.png", (dimensions.x/2)-400, 0, 800, 100, true));


	Tile* holding = nullptr;
	SDL_Point generalVelocity = { 0,0 };
	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_LEFT:  generalVelocity.x -= SCROLLSPEED; break;
					case SDLK_RIGHT:  generalVelocity.x += SCROLLSPEED; break;
					case SDLK_DOWN:  generalVelocity.y += SCROLLSPEED; break;
					case SDLK_UP:  generalVelocity.y -= SCROLLSPEED; break;
					case SDLK_ESCAPE:  done = true; break;
					case SDLK_SPACE:  SDL_ShowCursor(!SDL_ShowCursor(SDL_QUERY)); break;
					};
				}; break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:  generalVelocity.x += SCROLLSPEED; break;
				case SDLK_RIGHT:  generalVelocity.x -= SCROLLSPEED; break;
				case SDLK_DOWN:  generalVelocity.y -= SCROLLSPEED; break;
				case SDLK_UP:  generalVelocity.y += SCROLLSPEED; break;
				}; break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y }; break;
			case SDL_MOUSEBUTTONDOWN:
				if (holding == nullptr) {
					holding = new Tile(getMouseLocation().x,getMouseLocation().y,0,0,0); //final 0 is selected material
					tiles.push_back(holding);
				}else {
					holding = nullptr;
				}
			};
		};
		//end input while
		if (holding != nullptr) {
			holding->resize(getMouseLocation().x - holding->getRectan().x, getMouseLocation().y - holding->getRectan().y);
		}

		
		mainCharacter->adjustPosition(generalVelocity.x, generalVelocity.y);
		focus.x = mainCharacter->getRectan().x + mainCharacter->getRectan().w/2;
		focus.y = mainCharacter->getRectan().y + mainCharacter->getRectan().h/2;
		display();

	}
	//game ends here
}
void Game::display() {
	for (int x = 0; x < backgrounds.size(); x++) {
		Thing* theThing = backgrounds.at(x);
		theThing->upd8();
		//only drawSelf() things that need to be on the screen
		if (theThing->getVisible()) {
			theThing->blit_self();
		}
	}
	for (int x = 0; x < tiles.size(); x++) {
		Thing* theThing = tiles.at(x);
		theThing->upd8();
		//only drawSelf() things that need to be on the screen
		if (theThing->getVisible()) {
			theThing->blit_self();
		}
	}
	for (int x = 0; x < things.size(); x++) {
		Thing* theThing = things.at(x);
		theThing->upd8();
		//only drawSelf() things that need to be on the screen
		if (theThing->getVisible()) {
			theThing->blit_self();
		}
	}
	for (int x = 0; x < gui.size(); x++) {
		Thing* theThing = gui.at(x);
		theThing->upd8();
		//only drawSelf() things that need to be on the screen
		if (theThing->getVisible()) {
			theThing->blit_self();
		}
	}
	SDL_RenderPresent(r);
}


void Game::save() {

}

SDL_Point Game::getMouseLocation() {
	return { focus.x -(dimensions.x/2) +mouseLocation.x,  focus.y -(dimensions.y/2) +mouseLocation.y };
}
SDL_Point Game::getFocus() {
	return focus;
}
SDL_Rect Game::realignRectangle(SDL_Rect toRealign) {
	toRealign.x -= focus.x;
	toRealign.x += dimensions.x / 2;
	toRealign.y -= focus.y;
	toRealign.y += dimensions.y / 2;

	return toRealign;
}
SDL_Renderer* Game::getRenderer() {
	return r;
}