#pragma once
#include "Menu.h"

class Board;
class Piece;

class InPlayMenu : public Menu {
public:
	InPlayMenu(bool e);

	void draw(SDL_Renderer* r);
	void click(SDL_Point* p);

	void setFlipped(bool f);
	bool getFlipped();
	void setBoard(Board* bn);
	Board* getBoard(); 

	static void setup(SDL_Texture* ps, SDL_Texture* ss);

private:
	static SDL_Texture* pieceSprites;
	static SDL_Texture* selectorSprites;

	static SDL_Rect pieceRect;
	static SDL_Rect selectorRect;
	static SDL_Rect pieceRectStamper;
	static SDL_Rect selectorRectStamper;

	Board* b;
	Piece* holding;
	
	bool flipped;
	bool editMode;

	SDL_Point flipPoint(SDL_Point p);
};