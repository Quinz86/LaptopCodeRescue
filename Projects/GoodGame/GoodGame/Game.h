#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

#include "Clickable.h"
#include "Renderable.h"
#include "Updatable.h"

#include "MyOrderedList.h"

class Character;
class Chunk;

class Game {
public:
	static void setup();
	static void run();
	static void cleanup();

	static SDL_Rect* getScreenLocation();
	static double getZoomLevel();

	

private:
	static SDL_Window* MAINwindow;
	static SDL_Renderer* MAINrenderer;
	static bool done;
	static SDL_Point mouseLocation;
	static SDL_Rect screenLocation;
	static double zoomLevel;

	static std::vector<Clickable*> clickables;
	static std::vector<Updatable*> updatables;
	static MyOrderedList<Renderable*> renderables;



	static void handleClickNum(int num);
	static void setScreenFocus(int x, int y);

	static Character* mainCharacter;
	static Character* sideCharacter;
	static Chunk* floor1;
};