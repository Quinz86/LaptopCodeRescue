#include "Player.h"

//constructors
Player::Player(int xn, int yn):Thing(xn,yn,64,64,false){
	sprt = m->myTextureGet("imaspacecowboy.png");
}
Player::~Player() {

}

//other
void Player::setPosition(int x, int y) {
	rectan.x = x;
	rectan.y = y;
}
void Player::adjustPosition(int x, int y) {
	rectan.x += x;
	rectan.y += y;
}
void Player::setSprt(SDL_Texture* sprit) {
	sprt = sprit;
}

//virtual
void Player::upd8() {

}
void Player::blit_self() {
	SDL_RenderCopy(g->getRenderer(), sprt, NULL, &g->realignRectangle(getRectan()));
}