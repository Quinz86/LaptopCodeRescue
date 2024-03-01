#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "Game.h"
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "Thing.h"
#include "filesystem"
#include <iostream>
#include "TextureManager.h"
#include "Player.h"
#include "Tile.h"

#define DIR "Assets/Textures/" 

 

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);//??
	
	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto width2 = DM.w;
	auto height2 = DM.h;

	SDL_Window *MAINscreen = SDL_CreateWindow("GENERAL",
		0, 30, //SDL_WINDOWPOS_UNDEFINED
		width2, height2-70,                                             //these nums arent perfect
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 100, 0, 0, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);

	//setup here
	//we usin' a texturemanager now
	TextureManager mm = TextureManager(MAINrenderer);
	Tile::setMaterials(0, mm.myTextureGet("floor.png"));
	Tile::setMaterials(1, mm.myTextureGet("wood1.png"));
	Tile::setMaterials(2, mm.myTextureGet("water2.png"));

	// game code eventually goes here
	int w, h;
	SDL_GetWindowSize(MAINscreen, &w, &h);
	Game myGame = Game(MAINrenderer, w, h);
	Thing::setup(&mm,&myGame);

	myGame.run();

	SDL_Quit();

	return 0;
}

