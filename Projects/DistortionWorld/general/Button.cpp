#include "Button.h"

//constructor
Button::Button(int xn, int yn, int wn, int hn, int cv) {
	clickValue = cv;
	clickableArea = { xn, yn, wn, hn };
}
Button::~Button() {

}

//other
int Button::getClickValue() {
	return clickValue;
}
SDL_Rect Button::getClickableArea() {
	return clickableArea;
}