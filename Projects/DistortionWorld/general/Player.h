#pragma once

#include "Thing.h"
#include <string>

class Player : public Thing {
public:
	Player(int xn, int yn);
	~Player();
	void upd8();
	void blit_self();

	void setPosition(int x, int y);
	void adjustPosition(int x, int y);

	void setSprt(SDL_Texture* sprit);
private:
	SDL_Texture* sprt;

};

