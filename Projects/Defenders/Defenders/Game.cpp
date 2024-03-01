#include "Game.h"

Game::Game(SDL_Renderer* nr) {
	r = nr;
	players = std::vector<Player*>();
}

void Game::run() {
	bool done = false;
	int nextMode = 0;

	while (!done) {
		switch (nextMode) {
		case -1: done = true; break; //end game
		case 0: nextMode = mode0(); break; //loading
		case 1: nextMode = mode1(); break; //title screen
		case 2: nextMode = mode2(); break; // in game
		}
	}
}

int Game::mode0() {
	return 1;
}
int Game::mode1() {

}
int Game::mode2() {

}