#pragma once
#include "Useful.h"
#include <vector>
#include "SDL.h"
#include <string>

struct Memory {
	int memorability; //rename this, actually this is fine, i guess
	int goodness;
};


class AI {
public:
	AI(std::string filen, SDL_Renderer* r);
	AI(SDL_Renderer* r,int bx, int by);
	~AI();
	void update();
	SDL_Texture* getSprite();
	SDL_Rect* getRectan();
//	SDL_Point* getCenter();   ????????
	std::string getSaveFile();
	

private:
	//mechanical
	std::string saveFile;
	SDL_Rect rectan;
	SDL_Texture* sprite;
	SDL_Color hue;
	SDL_Point vel = { 0,0 };
	SDL_Point destination;
	void findNewDestination();

	//emotions
	std::vector<Memory> memories;
	int happinessE;  //sadness   -100/100 
	int angerE;     //???
	int fearE;       //???
	int curiosityE;
	int advanturE;

	//personality
	int happyP;
	int braveryP;

};