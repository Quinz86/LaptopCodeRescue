
#include <iostream>
#include <stdlib.h>
#include <stdio.h>




#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "filesystem"
#include <iostream>

#include "TextureManager.h"
#include "Game.h"




#define DEFAULT_PORT "41352"


int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("Needs an IP. Usage:\ntwixtclient.exe ###.###.###.###\n");
		return 2;
	}

	//====== SETUP THE VISUALS==========
	SDL_Init(SDL_INIT_VIDEO);//??
	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));

	SDL_Window *MAINscreen = SDL_CreateWindow("Twixt",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		576+(200), 576,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 128, 128, 128, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);
	//====== \SETUP THE VISUALS==========

	signed char tempColor = 0;
	bool tempTurn = false;


	//setups
	TextureManager::setup(MAINrenderer);
	Game::setup(MAINrenderer, argv[1]);// , tempColor, tempTurn, &ConnectSocket);




	//========= RUN THE GAME==============
	printf("Running Game\n");
	Game::run();
	//====================================



	//cleanups
	Game::cleanup();
	TextureManager::cleanup();

	/*
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		SDL_Quit();
		WSACleanup();
		return 1;
	}
	*/

	//close
	SDL_Quit();
	//closesocket(ConnectSocket);
	//WSACleanup();
	printf("Everything went swimmingly.");
	return 0;
}