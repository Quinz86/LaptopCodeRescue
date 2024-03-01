#include "Button.h"



//constructor
Button::Button(SDL_Rect* rr, int val) {
	rectan = rr;
	value = val;
}


int Button::click() {
	return value;
}
SDL_Rect* Button::getRectan() {
	return rectan;
}