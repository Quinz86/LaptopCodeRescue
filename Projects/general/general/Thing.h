#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "TextureManager.h"
#include "Game.h"


class Thing {
public:
	Thing(int xn, int yn, int wn, int hn, bool show);
	~Thing();
	SDL_Rect getRectan();
	bool getInvisible();

	virtual void upd8(); // consider making this =0, see polymorphism "abstract base classes" http://www.cplusplus.com/doc/tutorial/polymorphism/
	virtual void blit_self(); //this too?

	static void setup(TextureManager* mn, Game* gn);
protected:
	bool invisible;
	SDL_Rect rectan;

	static TextureManager* m;
	static Game* g;
	//add renderer to this list too so we dont ahve to get it from g every time maybe...?
};