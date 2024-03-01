#pragma once

#include "Updatable.h"
#include "Clickable.h"
#include "Renderable.h"

#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Character : public Updatable, public Clickable, public Renderable {
public:
	Character(SDL_Texture* spt, int xn, int yn, int wn, int hn);
	~Character();

	void update();
	void render(SDL_Renderer* r);
	int click(SDL_Point* point);
	SDL_Rect* getClickBox();
	int getFootPos();

	void moveBy(int dx, int dy);
	SDL_Rect* getRect();

	static bool compHeight(Character* c1, Character* c2);

	void addToVelocity(int x, int y);
private:
	SDL_Texture* sprite;
	SDL_Rect rectan;

	SDL_Point velocity;
};