#include "Thing.h"

//statics
TextureManager* Thing::m = nullptr;
Game* Thing::g = nullptr;
void Thing::setup(TextureManager* mn, Game* gn) {
	m = mn;
	g = gn;
}

//constructor
Thing::Thing(int xn, int yn, int wn, int hn, bool show) {
	rectan = { xn, yn, wn, hn };
	invisible = show;
}
Thing::~Thing() {

}


//other stuffs
SDL_Rect Thing::getRectan() {
	return rectan;
}
bool Thing::getInvisible() {
	return invisible;
}

//virtual
void Thing::upd8() {
	//there really shouldnt be any thing here
	//ever, if im not mistaken...
}
void Thing::blit_self() {
	SDL_RenderCopy(g->getRenderer(),m->myTextureGet("DefaultTexture.png"),NULL,&g->realignRectangle(getRectan()));
};
