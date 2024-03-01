#include "DiceSet.h"


//constructor
DiceSet::DiceSet(int nd, int nf, int x, int y, int diceDimension) : Renderable(x,y,diceDimension*nd,diceDimension), Updatable(){
	diceList = std::vector<Die*>();
	for (int q = 0; q < nd; q++) {
		diceList.push_back(new Die(nf,x+(q*diceDimension),y,diceDimension));
	}
}
DiceSet::~DiceSet() {
	for (int x = 0; x < diceList.size(); x++) {
		delete diceList.at(x);
	}
}


//inherited
void DiceSet::render(SDL_Renderer* r) {
	for (int d = 0; d < diceList.size(); d++) {
		diceList.at(d)->render(r);
	}
}
void DiceSet::update() {
	for (int d = 0; d < diceList.size(); d++) {
		diceList.at(d)->update();
	}
}


//methods
int DiceSet::getHighest() {
	int highest = 0;
	for (int d = 0; d < diceList.size(); d++) {
		if (diceList.at(d)->getShowNum() > highest) {
			highest = diceList.at(d)->getShowNum();
		}
	}
	return highest;
}
void DiceSet::rollAll() {
	for (int d = 0; d < diceList.size(); d++) {
		diceList.at(d)->roll();
	}
}

int DiceSet::getNumDice() {
	return diceList.size();
}
