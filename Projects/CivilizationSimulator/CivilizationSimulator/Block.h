#pragma once
#include "SDL.h"


class Block {
public:
	Block();
	virtual SDL_Texture* getSprite()=0;
protected:
private:
};