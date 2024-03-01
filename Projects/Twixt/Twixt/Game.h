#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "MyServerWrapper.h"
#include "Message.h"

#include "Board.h"
#include "Peg.h"

#define DEFAULT_PORT "41352"

class Game {
public:
	static void setup(SDL_Renderer* rn, std::string internetprotocol);
	static void run();
	static void cleanup();


private:
	static bool done;
	static bool myColor; //true = red, false = black
	static bool myTurn;
	static bool pegLink; //true = peg, false = link
	static bool placedPeg;
	static bool changesMade;
	static SDL_Point selectedPeg;
	static bool selecting;

	static int connectingTimer; //-1 = not connected, -2 = connected, >=0  =  connecting
	static int waitingTimer; // >=0 waiting, -1 = not waiting

	static Board realBoard;
	static Board editBoard;
	static void resetEdit();

	static SDL_Renderer* r;
	static SDL_Point mouseLocation;
	static void handleClick();
	static void spaceBar();

	static SDL_Rect board_RECT;
	static SDL_Rect menu_RECT;
	static SDL_Rect pegB_RECT;
	static SDL_Rect linkB_RECT;
	static SDL_Rect finishmoveB_RECT;
	static SDL_Rect resetB_RECT;
	static SDL_Rect wating_RECT;
	static SDL_Rect conB_RECT;
	static SDL_Rect coning_RECT;
	static SDL_Rect exitB_RECT;

	//==================================

	static MyServerWrapper<Message> serv;
	static std::string ip;

};