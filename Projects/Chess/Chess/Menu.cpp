#include "Menu.h"
#include "Button.h"
#include "Game.h"
#include <iostream>

#define BORDER_WIDTH 8

//static
Game* Menu::g = nullptr;
SDL_Texture* Menu::bg = nullptr;
SDL_Texture* Menu::blueTransparent = nullptr;
SDL_Texture* Menu::greySolid = nullptr;

void Menu::setup(Game* gn, SDL_Texture* backG, SDL_Texture* transpBlue, SDL_Renderer* r) {
	g = gn;

	bg = backG;
	blueTransparent = transpBlue;

	SDL_Surface* surf;
	surf = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0); //the 2s can probably be 1s
	
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 123, 123, 123));
	greySolid = SDL_CreateTextureFromSurface(r, surf);

	SDL_FreeSurface(surf);


}


//constructor
Menu::Menu() {
	buttons = std::vector<Button*>();
}
Menu::~Menu() {
	for (int x = 0; x < buttons.size(); x++) {
		delete buttons.at(x);
	}
}



void Menu::addButton(Button* b) {
	buttons.push_back(b);
}
void Menu::draw(SDL_Renderer* r) {
	SDL_RenderCopy(r, bg, NULL, NULL); //background first
	//now buttons
	Button* b;
	for (int x = 0; x < buttons.size(); x++) {
		b = buttons.at(x);
		
		SDL_RenderCopy(r, greySolid, NULL, b->getRect()); //draw grey box here
		g->drawWords(b->getRect(),b->getDisplay()); //draw words
		//draw border here 
		if (b->getHighlighted()) {
			SDL_Rect rectan;

			rectan = {b->getRect()->x - BORDER_WIDTH, b->getRect()->y - BORDER_WIDTH, BORDER_WIDTH + b->getRect()->w, BORDER_WIDTH};
			SDL_RenderCopy(r, blueTransparent, NULL, &rectan);
			rectan = { b->getRect()->x - BORDER_WIDTH, b->getRect()->y, BORDER_WIDTH, b->getRect()->h + BORDER_WIDTH };
			SDL_RenderCopy(r, blueTransparent, NULL, &rectan);
			rectan = { b->getRect()->x, b->getRect()->y + b->getRect()->h, b->getRect()->w + BORDER_WIDTH, BORDER_WIDTH };
			SDL_RenderCopy(r, blueTransparent, NULL, &rectan);
			rectan = { b->getRect()->x + b->getRect()->w , b->getRect()->y - BORDER_WIDTH, BORDER_WIDTH, BORDER_WIDTH + b->getRect()->h };
			SDL_RenderCopy(r, blueTransparent, NULL, &rectan);
		}
	}
}

void Menu::click(SDL_Point* p) {
	Button* b;
	for (int x = 0; x < buttons.size(); x++) {
		b = buttons.at(x);
		if ( SDL_PointInRect(p, b->getRect()) && b->getCLickable() ){
			b->click(g);
			break;
		}
	}
}
void Menu::mouseMoved(SDL_Point* p) {
	Button* b;
	for (int x = 0; x < buttons.size(); x++) {
		b = buttons.at(x);
		if (SDL_PointInRect(p, b->getRect()) && b->getCLickable()) {
			b->setHighlighted(true);
		}else {
			b->setHighlighted(false);
		}
	}
}