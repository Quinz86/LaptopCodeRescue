#include "AI.h"
#include <fstream>
#include <iostream>   //??? un-needed?

//constructor
AI::AI(std::string filen, SDL_Renderer* r) {
	saveFile = filen;
	int xn, yn, wn, hn;
	Uint8 rn, gn, bn;    ///consider rn,gn,bn :: unsigned char ---->http://en.cppreference.com/w/cpp/language/types

	std::fstream myFile;
	myFile.open( saveFile, std::ios::in | std::ios::binary);
	myFile.read((char*)&xn, sizeof(int)); 
	myFile.read((char*)&yn, sizeof(int)); 
	myFile.read((char*)&wn, sizeof(int)); 
	myFile.read((char*)&hn, sizeof(int)); 
	myFile.read((char*)&rn, sizeof(Uint8));
	myFile.read((char*)&gn, sizeof(Uint8));
	myFile.read((char*)&bn, sizeof(Uint8));
	myFile.close();

	rectan = { xn, yn, wn, hn };
	hue = { rn,gn,bn };

	SDL_Surface* s = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0); //the 2s can probably be 1s
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, rn, gn, bn));
	sprite = SDL_CreateTextureFromSurface(r, s);
	SDL_FreeSurface(s);

	findNewDestination();
};
AI::AI(SDL_Renderer* r, int bx, int by) {
	saveFile = "AIs/" + std::to_string(rand()%10000) + ".bin"; //this needs to be random and unique
	//random, yes, but unique, not yet
	
	int wn = rand() % 32;
	int hn = rand() % 32;
	rectan = { bx, by, wn, hn };
	//adv color gen????
	hue = { (Uint8)(rand() % 0xff) , (Uint8)(rand() % 0xff), (Uint8)(rand() % 0xff) };

	SDL_Surface* s = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0); //the 2s can probably be 1s
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, hue.r, hue.g, hue.b));
	sprite = SDL_CreateTextureFromSurface(r, s);
	SDL_FreeSurface(s);

	findNewDestination();
}
AI::~AI() {
	SDL_DestroyTexture(sprite);
	
	std::fstream myFile;
	myFile.open(saveFile,std::fstream::binary | std::fstream::out | std::fstream::trunc); //trunc means previous data in file is deleted
	myFile.write((char*)&rectan.x, sizeof(int));
	myFile.write((char*)&rectan.y, sizeof(int));
	myFile.write((char*)&rectan.w, sizeof(int));
	myFile.write((char*)&rectan.h, sizeof(int));
	myFile.write((char*)&hue.r, sizeof(Uint8));
	myFile.write((char*)&hue.g, sizeof(Uint8));
	myFile.write((char*)&hue.b, sizeof(Uint8));
	myFile.close();
	

}

void AI::findNewDestination() {
	destination = { rand() % (700 - rectan.w),rand() % (700 - rectan.h) };
}
void AI::update() {
	
	//pathfinding
	if (rectan.x > destination.x) {
		vel.x = -1;
	}else if (rectan.x < destination.x) {
		vel.x = 1;
	}else {
		vel.x = 0;
	};
	if (rectan.y > destination.y) {
		vel.y = -1;
	}else if (rectan.y < destination.y) {
		vel.y = 1;
	}else {
		vel.y = 0;
	};

	//movement
	rectan.x += vel.x;
	rectan.y += vel.y;

	//walls
	if (rectan.x >= 700 - rectan.w) {
		rectan.x = 700 - rectan.w;
	}else if (rectan.x <= 0) {
		rectan.x = 0;
	};
	if (rectan.y >= 700 - rectan.h) {
		rectan.y = 700 - rectan.h;
	}else if (rectan.y <= 0) {
		rectan.y = 0;
	};
	if (rectan.x == destination.x && rectan.y == destination.y) {
		findNewDestination();
	}

}

SDL_Texture* AI::getSprite() {
	return sprite;
}
SDL_Rect* AI::getRectan() {
	return &rectan;
}
std::string AI::getSaveFile() {
	return saveFile;
}