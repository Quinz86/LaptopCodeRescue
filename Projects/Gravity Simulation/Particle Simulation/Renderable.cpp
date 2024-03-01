#include "Renderable.h"

Renderable::Renderable(int x, int y, int w, int h) : Renderable(x,y,w,h,0,0){
}
Renderable::Renderable(int x, int y, int w, int h, int xd, int yd) {
	xpos = x;
	ypos = y;
	width = w;
	height = h;

	xDisplacement = xd;
	yDisplacement = yd;

	updateRectan();
}
Renderable::~Renderable() {

}



void Renderable::updateRectan() {
	rectan = { xpos - xDisplacement,ypos - yDisplacement,width,height };
}
SDL_Rect* Renderable::getRect() {
	updateRectan();
	return &rectan;
}

void Renderable::move(int x, int y) {
	xpos = x;
	ypos = y;
}