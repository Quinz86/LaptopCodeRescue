#include "Game.h"

//constructor&destructor
Game::Game(SDL_Renderer* nr, int w, int h) {
	r = nr;
	resolution = { w,h };
}
Game::~Game() {

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
					case SDLK_LEFT:   break;
					case SDLK_RIGHT:   break;
					case SDLK_DOWN: break;
					case SDLK_UP:   break;
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

		
		
		
		SDL_RenderPresent(r);
		SDL_Delay(5);
	}//end gameloop

}