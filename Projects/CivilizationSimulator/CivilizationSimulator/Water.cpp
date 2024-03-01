#include "Water.h"

SDL_Texture* Water::sprt = nullptr;

Water::Water() {

}

void Water::setSprt(SDL_Texture* s) {
	sprt = s;
}

SDL_Texture* Water::getSprite() {
	return sprt;
}