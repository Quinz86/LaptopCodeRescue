#include "Slider.h"
#include "TextureManager.h"



//static
SDL_Texture* Slider::Ssprite = nullptr;
SDL_Texture* Slider::Csprite = nullptr;
void Slider::setup() {
	Ssprite = TextureManager::myTextureGet("Slider.png");
	Csprite = TextureManager::myTextureGet("SliderClick.png");
}



//constructors
Slider::Slider(int x, int y, int w, int h, int m) : Renderable(x,y,w,h),Clickable() {
	max = m;
	clickerRectan = {x,y,w,w/2};
}
Slider::~Slider() {

}

int Slider::getValue() {
	return min + (int)round(clickerPos * (max - min));
}
void Slider::setMax(int m) {
	max = m;
}


//inherited
void Slider::render(SDL_Renderer* r) {
	clickerRectan = { clickerRectan.x, getRect()->y + (int)round(clickerPos*getRect()->h) - clickerRectan.h/2,clickerRectan.w,clickerRectan.h };
	SDL_RenderCopy(r, Ssprite, NULL, getRect());
	SDL_RenderCopy(r, Csprite, NULL, &clickerRectan);
}
SDL_Rect* Slider::getClickBox() {
	return getRect();
}
int Slider::click(SDL_Point* point) {
	clickerPos = ((point->y - getRect()->y))*1.0 / (getRect()->h);
	return 0;
}