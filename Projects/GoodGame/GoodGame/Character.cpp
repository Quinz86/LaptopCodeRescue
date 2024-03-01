#include "Character.h"
#include "Game.h"


//statics

bool Character::compHeight(Character* c1, Character* c2) {
	if (c1->getRect()->y > c2->getRect()->y) {
		return true;
	}else {
		return false;
	}
}




//constructors
Character::Character(SDL_Texture* spt, int xn, int yn, int wn , int hn ) : Renderable(),Clickable(),Updatable(){
	sprite = spt;
	velocity = { 0,0 };
	rectan = { xn,yn,wn,hn };
}
Character::~Character() {

}



//inherited main 3
void Character::update() {
	moveBy(velocity.x, velocity.y);
}
void Character::render(SDL_Renderer* r) {
	SDL_Rect tempRect = { getRect()->x - Game::getScreenLocation()->x  ,
						  getRect()->y - Game::getScreenLocation()->y  ,
						  getRect()->w   ,
						  getRect()->h};
	SDL_RenderCopy(r,sprite,NULL,&tempRect);
}
int Character::click(SDL_Point* point) {
	return 1;
}
SDL_Rect* Character::getClickBox() {
	return getRect();
}
int Character::getFootPos() {
	return getRect()->y + getRect()->h; //bottom of rect
}




//methods
void Character::addToVelocity(int x, int y) {
	velocity.x += x;
	velocity.y += y;
}
void Character::moveBy(int dx, int dy) {
	rectan.x += dx;
	rectan.y += dy;
}
SDL_Rect* Character::getRect() {
	return &rectan;
}