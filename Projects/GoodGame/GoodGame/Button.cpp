#include "Button.h"
#include <iostream>
#include "TextureManager.h"

//static
SDL_Texture* Button::sprite = nullptr;
void Button::setUp() {
	sprite = TextureManager::myTextureGet("BlueButton.png");
	//sprite = TextureManager::myTextureGet("SliderClick.png");
}

//constructor
Button::Button(std::string disp, int x, int y, int w, int h, int cN) : Renderable(x, y, w, h), Clickable(){
	display = new WordBox(x+(int)(0.2*w),y+(int)(0.2*h),(int)(0.6*w),(int)(0.6*h),disp);
	//display = WordBox(1,1,1,1,"sdf");
	clickNum = cN;
}
Button::~Button() {
	delete display;
}



void Button::render(SDL_Renderer* r) {
	SDL_RenderCopy(r, sprite, NULL, getRect());
	display->render(r);
}
int Button::click(SDL_Point* point) { //0 = do nothing
	return clickNum;
}
SDL_Rect* Button::getClickBox() {
	return getRect();
}