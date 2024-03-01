#include "Mountain.h"

SDL_Texture* Mountain::sprt = nullptr;

Mountain::Mountain() {

}

void Mountain::setSprt(SDL_Texture* s) {
	sprt = s;
}

SDL_Texture* Mountain::getSprite() {
	return sprt;
}