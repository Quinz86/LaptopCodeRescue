#include "Renderable.h"

Renderable::Renderable(int x, int y, int w, int h) {
	rectan = { x, y, w, h };
}
Renderable::~Renderable() {

}




SDL_Rect* Renderable::getRect() {
	return &rectan;
}