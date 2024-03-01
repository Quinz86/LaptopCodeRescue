#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "filesystem"
#include <iostream>
#include <fstream>

#include "TextureManager.h"

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);//??

	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));


	SDL_Window *MAINscreen = SDL_CreateWindow("GENERAL",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		497, 257,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 100, 100, 100, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);


	//setup here
	//we usin' a texturemanager now


	// game code eventually goes here
	int w, h;
	SDL_GetWindowSize(MAINscreen, &w, &h);


	//setups
	TextureManager::setUp(MAINrenderer);
	SDL_Texture* earth = TextureManager::myTextureGet("equidistant_cylindrical_projection_earth.png");
	SDL_Texture* hit = TextureManager::myTextureGet("hit.png");



	//========= RUN THE GAME==============

	SDL_RenderCopy(MAINrenderer,earth,NULL,NULL);
	SDL_RenderPresent(MAINrenderer);

	SDL_Rect hitStamper = {0,0,5,5};
	int xStart = 34;
	int yStart = 21;


	std::string line;
	std::ifstream myfile("meteor locations.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::string latString = line.substr(12, 9);
			std::string longString = line.substr(34, 10);
			double latitude = stod(latString);
			double longitude = stod(longString);
			std::cout << "Latitude:"<<latitude<<"\nLongitude:"<<longitude<< "\n\n";
			
			hitStamper.x = (249+(longitude*(249-xStart)/180)) - 2;
			hitStamper.y = (128-(latitude*(128-yStart)/90)) - 2;
			SDL_RenderCopy(MAINrenderer,hit,NULL,&hitStamper);
		
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";

	SDL_RenderPresent(MAINrenderer);

	//begin game loop
	SDL_Event event;
	bool done = false;
	while (!done) {
		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			}
		}
	}
	//====================================



	//cleanups
	TextureManager::cleanUp();

	SDL_Quit();

	return 0;
}

