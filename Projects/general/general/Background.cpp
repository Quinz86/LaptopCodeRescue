#include "Background.h"

//constructors
Background::Background(std::string spriten, int x, int y, int w, int h, bool sw):Thing(x,y,w,h,false) {
	sprite = m->myTextureGet(spriten);
	scrollWith = sw;
}
Background::~Background() {

}


//other

//virtual
void Background::blit_self() {
	if (scrollWith) {
		SDL_RenderCopy(g->getRenderer(), sprite, NULL, &getRectan());
	}else {
		SDL_RenderCopy(g->getRenderer(), sprite, NULL, &g->realignRectangle(getRectan()));
	}
}
void Background::upd8() {

}
