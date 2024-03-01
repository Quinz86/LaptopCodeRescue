#include "Living.h"

//constructor
Living::Living(int nx, int ny, int nw, int nh , SDL_Texture* nsprite) {
	rectan = { nx - (nw/2), ny - (nh/2) ,nw, nh };
	sprite = nsprite;
}

void Living::update() {
	rectan.x += vel.x;
	rectan.y += vel.y;
}
SDL_Point Living::getLoc() {
	return {rectan.x + (rectan.w/2), rectan.y + (rectan.h/2)};
}
SDL_Texture* Living::getSprite() {
	return sprite;
}
SDL_Rect* Living::getRectan() {
	return &rectan;
}