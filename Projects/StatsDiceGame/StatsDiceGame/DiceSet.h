#pragma once
#include "Renderable.h"
#include "Updatable.h"
#include <vector>
#include "Die.h"
#include "SDL.h"
#include "SDL_image.h"

class DiceSet : public Renderable, public Updatable {
public:
	DiceSet(int nd, int nf, int x, int y, int diceDimension);
	~DiceSet();

	int getHighest();
	void rollAll();
	int getNumDice();


	void render(SDL_Renderer* r);
	void update();
private:
	std::vector<Die*> diceList;
};