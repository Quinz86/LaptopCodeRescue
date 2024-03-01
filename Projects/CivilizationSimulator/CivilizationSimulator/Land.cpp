#include "Land.h"

SDL_Texture* Land::sprt = nullptr;

Land::Land() {

}

void Land::setSprt(SDL_Texture* s) {
	sprt = s;
}

SDL_Texture* Land::getSprite() {
	return sprt;
}