#pragma once

#include "SDL.h"



#define F0 0
#define F1 (1.0/7)
#define F2 (2.0/7)
#define F3 (3.0/7)
#define F4 (4.0/7)
#define F5 (5.0/7)
#define F6 (6.0/7)
#define F7 1
void getColor(double fraction, SDL_Renderer* r) {
	if (fraction < F0 || fraction > F7 ) {
		SDL_SetRenderDrawColor(r, 128, 128, 128, 255);
	}
	else if (fraction < F1) {
		SDL_SetRenderDrawColor(r,
			255,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255);
	}
	else if (fraction < F2) {
		fraction -= F1;
		SDL_SetRenderDrawColor(r,
			255,
			((Uint8)floor(255 * (fraction / F1))),
			0,
			255);
	}
	else if (fraction < F3) {
		fraction -= F2;
		SDL_SetRenderDrawColor(r,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255,
			0,
			255);
	}
	else if (fraction < F4) {
		fraction -= F3;
		SDL_SetRenderDrawColor(r,
			0,
			255,
			((Uint8)floor(255 * (fraction / F1))),
			255);
	}
	else if (fraction < F5) {
		fraction -= F4;
		SDL_SetRenderDrawColor(r,
			0,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255,
			255);
	}
	else if (fraction < F6) {
		fraction -= F5;
		SDL_SetRenderDrawColor(r,
			((Uint8)floor(255 * (fraction / F1))),
			0,
			255,
			255);
	}
	else if (fraction < F7) {	// fraction < F7
		fraction -= F6;
		SDL_SetRenderDrawColor(r,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			0,
			255 - ((Uint8)floor(255 * (fraction / F1))),
			255);
	}
	else {
		SDL_SetRenderDrawColor(r, 128, 128, 128, 255);
	}
}