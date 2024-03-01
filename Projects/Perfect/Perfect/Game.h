#pragma once



#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

class Game {
	public:
		static void setup();
		static void run();
		static void cleanup();
	
	private:
		static void handleClick();

		static bool done;
		static SDL_Point mouseLocation;
		
		static int animationTimer; //reusable
		
		
};