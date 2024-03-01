#include "Thing.h"

//statics
TextureManager* Thing::m = nullptr;
Game* Thing::g = nullptr;

void Thing::setup(TextureManager* mn, Game* gn, SDL_Texture* defaultSpt) {
	m = mn;
	g = gn;
	defaultSprite = defaultSpt;
}

//constructor
Thing::Thing(int xn, int yn, int wn, int hn, bool show) {
	rectan = { xn, yn, wn, hn };
	visible = show;
}
Thing::~Thing() {

}


//other stuffs
SDL_Rect Thing::getRectan() {
	return rectan;
}
bool Thing::getVisible() {
	return visible;
}

//virtual
void Thing::blit_self() {
	SDL_RenderCopy(g->getRenderer(),getSprite(),NULL,&g->realignRectangle(getRectan()));
};
SDL_Texture* Thing::getSprite() {
	return defaultSprite;
}
