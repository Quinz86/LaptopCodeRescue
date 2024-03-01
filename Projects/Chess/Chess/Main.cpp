#include "SDL.h"
#include "SDL_image.h"

#include <utility>
#include <time.h>
#include <thread>
#include <chrono>
#include <stdlib.h> 
#include <windows.h> //sleep
#include <fstream>
#include <iostream>
#include <string>

#include "Game.h"
#include "Button.h" //might not need
#include "Menu.h"
#include "InPlayMenu.h"
//probablu should go through these ^ at the end and delete the ones i dont need



int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));


	SDL_Window *MAINscreen = SDL_CreateWindow("Chess",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		520, 520,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	SDL_SetRenderDrawColor(MAINrenderer, 0, 0, 10, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);


	//file testing
	/*
	int bar = 8778;
	std::fstream fileTest;
	fileTest.open("Games/something.dat", std::ios::out | std::ios::binary);
	fileTest.write((char*)&bar, sizeof(int));
	fileTest.close();

	int foo;
	fileTest.open("Games/something.dat", std::ios::in | std::ios::binary);
	fileTest.read((char*)&foo, sizeof(int));
	fileTest.close();
	std::cout << foo << std::endl;
	*/

	// game code eventually goes here

	std::vector<SDL_Texture*> textures = std::vector<SDL_Texture*>();

		std::vector<const char*> pics = std::vector<const char*>();
		pics.push_back("Sprites/titleScreen.png");      //0     logo
		pics.push_back("Sprites/font.png");             //1
		pics.push_back("Sprites/chessBoard.png");       //2
		pics.push_back("Sprites/pieces.png");           //3
		pics.push_back("Sprites/selectors.png");        //4
		pics.push_back("Sprites/highlights.png");       //5
		

		SDL_Surface* surf = nullptr;
		for (int x = 0; x < pics.size(); x++) {
			surf = IMG_Load( pics.at(x) );
			SDL_Texture* t = SDL_CreateTextureFromSurface(MAINrenderer, surf);
			textures.push_back(t);
		}
		SDL_FreeSurface(surf);


	Game::setup(textures.at(0), textures.at(1)); //always do this last

		Game myGame = Game(MAINrenderer);

	Menu::setup(&myGame, textures.at(2), textures.at(5), MAINrenderer);
	InPlayMenu::setup(textures.at(3),textures.at(4));

		myGame.run();

	//Sleep(20*1000);
	
	for (int x = 0; x < textures.size(); x++) {
		SDL_DestroyTexture(textures.at(x));
	}


	SDL_DestroyRenderer(MAINrenderer);
	SDL_DestroyWindow(MAINscreen);
	SDL_Quit();

	return 0;
}

