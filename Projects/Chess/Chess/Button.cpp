#include "Button.h"
#include "Game.h"




Button::Button(int n, SDL_Rect rectan, std::string disp, bool c) {
	num = n;
	box = rectan;
	display = disp;
	clickable = c;
	highlighted = false;
}

void Button::click(Game* g) {
	highlighted = false;
	g->buttonReaction(num, this);
}


SDL_Rect* Button::getRect() {
	return &box;
}


std::string Button::getDisplay() {
	return display;
}
void Button::setDisplay(std::string d) {
	display = d;
}
bool Button::getCLickable() {
	return clickable;
}
void Button::setClickable(bool c) {
	clickable = c;
}
bool Button::getHighlighted() {
	return highlighted;
}
void Button::setHighlighted(bool h) {
	highlighted = h;
}