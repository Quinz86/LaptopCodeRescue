#include "Game.h"
#include "Renderable.h"
#include "Button.h"
#include "Clickable.h"
#include <iostream>
#include "SDL_image.h"
#include "Updatable.h"
#include "Die.h"
#include "WordBox.h"
#include "DiceSet.h"
#include "Slider.h"

#define DIR "Assets/Textures/" 
#define RATIO 1.0


//static
void Game::setup(SDL_Renderer* r) {
	
}



//constructors
Game::Game(int sW, int sH, SDL_Renderer* r) {
	screenWidth = sW;
	screenHeight = sH;
	rend = r;

	bankSet = new DiceSet(2,4,100,300,64);
	playerSet = new DiceSet(1,6,100,400,64);

	toUpdate.push_back(bankSet);
	toUpdate.push_back(playerSet);
	toRender.push_back(bankSet);
	toRender.push_back(playerSet);
}
Game::~Game() {
	delete bankSet;
	delete playerSet;
}


//methods
void Game::run() {

	Button* b1 = new Button("ROLL",40,40,600,200,1);
	toRender.push_back(b1);
	toClick.push_back(b1);
	Button* b2 = new Button("BUY EXTRA DIE", 40, 575, 800, 100, 2);
	toRender.push_back(b2);
	toClick.push_back(b2);

	Button* b3 = new Button("OK", 900, 575, 200, 100, 3);
	toRender.push_back(b3);
	toClick.push_back(b3);

	Slider* s1 = new Slider(1150, 25,100,650,1000); //bet slider
	toRender.push_back(s1);
	toClick.push_back(s1);

	WordBox* ph = new WordBox(1000, 400, 64, 64, "*"); // player highest display
	toRender.push_back(ph);
	WordBox* bh = new WordBox(1000, 300, 64, 64, "*"); // bank highest display
	toRender.push_back(bh);

	WordBox* mon = new WordBox(700, 60, 80, 100, "$100"); // money display
	toRender.push_back(mon);
	WordBox* be = new WordBox(750, 500, 100, 50, "BET: 100");  //bet display
	toRender.push_back(be);
	

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
					}
				}; break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) { // left click
					for (int x = 0; x < toClick.size(); x++) {
						if (toClick.at(x) == s1 && addedADie ) { continue; };
						if ( SDL_PointInRect(&mouseLocation,toClick.at(x)->getClickBox()) ) {
							respondToClickNum(toClick.at(x)->click(&mouseLocation));
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
		for (int x = 0; x < toUpdate.size(); x++) {
			toUpdate.at(x)->update();
		}

		ph->changeWords(std::to_string(playerSet->getHighest()));
		bh->changeWords(std::to_string(bankSet->getHighest()));
		mon->changeWords("$" + std::to_string(playerMoney/100) + "." + std::to_string(playerMoney%100));
		s1->setMax(playerMoney);
		if (!addedADie) {
			playerBet = s1->getValue();
		}
		be->changeWords("BET: $" + std::to_string(playerBet / 100) + "." + std::to_string(playerBet % 100));
		

		//begin drawing
		SDL_RenderClear(rend);
		for (int x = 0; x < toRender.size(); x++) {
			toRender.at(x)->render(rend);
		}
		SDL_RenderPresent(rend);
	}
	//after game loop
	delete b1;

}

void Game::respondToClickNum(int n) {
	switch (n) {
	case 1: if (ok) { bankSet->rollAll(); playerSet->rollAll(); } ok = false;  break;   ///roll
	case 2: if (ok && playerMoney - 0.2*playerBet >= 0) { replacePlayerSet(playerSet->getNumDice() + 1); playerMoney -= 0.2*playerBet; addedADie = true; } break;   //buy
	case 3: if (bankSet->getHighest() != 0 && playerSet->getHighest() != 0) {
				ok = true;
				if (playerSet->getHighest() > bankSet->getHighest()) {
					playerMoney += playerBet*RATIO;
				}else {
					playerMoney -= playerBet;
				}
				replacePlayerSet(1); 
				replaceBankSet(2);
				
				addedADie = false;
				if (playerMoney <= 0) {
					done = true;
				}
			} break;   //ok
	}
}
//==========================================



void Game::replacePlayerSet(int newNumDice) {
	for (int a = 0; a < toUpdate.size(); a++) {
		if (toUpdate.at(a) == playerSet) {
			toUpdate.erase(toUpdate.begin() + a);
			a--;
		}
	}
	for (int a = 0; a < toRender.size(); a++) {
		if (toRender.at(a) == playerSet) {
			toRender.erase(toRender.begin() + a);
			a--;
		}
	}
	delete playerSet;

	playerSet = new DiceSet(newNumDice, 6, 100, 400, 64);
	toUpdate.push_back(playerSet);
	toRender.push_back(playerSet);
}
void Game::replaceBankSet(int newNumDice) {
	for (int a = 0; a < toUpdate.size(); a++) {
		if (toUpdate.at(a) == bankSet) {
			toUpdate.erase(toUpdate.begin() + a);
			a--;
		}
	}
	for (int a = 0; a < toRender.size(); a++) {
		if (toRender.at(a) == bankSet) {
			toRender.erase(toRender.begin() + a);
			a--;
		}
	}
	delete bankSet;

	bankSet = new DiceSet(newNumDice, 4, 100, 300, 64);
	toUpdate.push_back(bankSet);
	toRender.push_back(bankSet);
}