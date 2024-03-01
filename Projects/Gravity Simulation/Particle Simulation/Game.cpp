#include "Game.h"
#include "Renderable.h"
#include "Clickable.h"
#include <iostream>
#include "SDL_image.h"
#include "Updatable.h"
#include "Particle.h"



//static
void Game::setup(SDL_Renderer* r) {
	
}


//constructors
Game::Game(int sW, int sH, SDL_Renderer* r) {
	screenWidth = sW;
	screenHeight = sH;
	rend = r;

	resetWithXParticles(4);

	Particle::setup(this);

}
Game::~Game() {
}


//methods
int Game::getScreenWidth() {
	return screenWidth;
}
int Game::getScreenHeight() {
	return screenHeight;
}
std::vector<Particle*>* Game::getParticleListPointer() {
	return &particleList;
}
void Game::resetWithXParticles(int x) {
	for (int y = 0; y < particleList.size(); y++) {
		delete particleList.at(y);
	}
	particleList.clear();
	for (int y = 0; y < x; y++) {
		Particle* p = new Particle(rand() % screenWidth, rand() % screenHeight, rand() % 20 + 40);
		particleList.push_back(p);
		//toRender.push_back(p);
		//toUpdate.push_back(p);
	}
}




//run method
void Game::run() {


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
					case SDLK_0: resetWithXParticles(0 * 3); break;
					case SDLK_1: resetWithXParticles(1 * 3); break;
					case SDLK_2: resetWithXParticles(2 * 3); break;
					case SDLK_3: resetWithXParticles(3 * 3); break;
					case SDLK_4: resetWithXParticles(4 * 3); break;
					case SDLK_5: resetWithXParticles(5 * 3); break;
					case SDLK_6: resetWithXParticles(6 * 3); break;
					case SDLK_7: resetWithXParticles(7 * 3); break;
					case SDLK_8: resetWithXParticles(8 * 3); break;
					case SDLK_9: resetWithXParticles(9 * 3); break;

					}
				}; break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) { // left click
					for (int x = 0; x < toClick.size(); x++) {
						if ( SDL_PointInRect(&mouseLocation,toClick.at(x)->getClickBox()) ) {
							respondToClickNum(toClick.at(x)->click());
						}
					}
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) { // right click

				}; break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y };
				break;
			}
				
		}

		//begin updating
		for (int x = 0; x < particleList.size(); x++) {
			//std::cout << "IM UPDATING "<< x << std::endl;
			//toUpdate.at(x)->update();
			particleList.at(x)->update();
		}

		//merge
		for (int x = 0; x < particleList.size(); x++) {
			Particle* m = particleList.at(x);
			for (int z = 0; z < particleList.size(); z++) {
				Particle* o = particleList.at(z);
				if (o != m) {
					if (Particle::calculateDistance(m, o) < 3.0) {
						m->addMass(o->getMass());
						particleList.erase(particleList.begin()+z);
						delete o;
						z--;
						x--;
					}
				}

			}
		}

		//begin drawing
		SDL_RenderClear(rend);
		for (int x = 0; x < particleList.size(); x++) {
			//toRender.at(x)->render(rend);
			particleList.at(x)->render(rend);
		}
		SDL_RenderPresent(rend);
	}
	//after game loop
	
}

void Game::respondToClickNum(int n) {
	switch (n) {
	default: break;
	}
}