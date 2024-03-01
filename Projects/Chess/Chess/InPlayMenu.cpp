#include "InPlayMenu.h"
#include "Board.h"
#include "Piece.h"
#include "PieceType.h"
#include <iostream>
#include "AllThePieces.h"


//static
SDL_Texture* InPlayMenu::pieceSprites = nullptr;
SDL_Texture* InPlayMenu::selectorSprites = nullptr;
SDL_Rect InPlayMenu::pieceRect = {0,0,65,65};
SDL_Rect InPlayMenu::selectorRect = {0,0,65,65};
SDL_Rect InPlayMenu::pieceRectStamper = { 0,0,65,65 };
SDL_Rect InPlayMenu::selectorRectStamper = { 0,0,65,65 };


void InPlayMenu::setup(SDL_Texture* ps, SDL_Texture* ss) {
	pieceSprites = ps;
	selectorSprites = ss;
}


//constructor
InPlayMenu::InPlayMenu(bool e) : Menu() {
	//Menu();
	b = nullptr;
	holding = nullptr;
	
	flipped = false;
	editMode = e;
	
}

void InPlayMenu::click(SDL_Point* p) {
	try {
		if (b) {
			SDL_Point s = { p->x / 65, p->y / 65 };
			if (flipped) {
				s = flipPoint(s);
			}

			if (editMode) {
				Piece* original = b->getPieceAt(s.x, s.y);
				if (!original) {
					b->setPieceAt(s.x, s.y, new Pawn(true));
				}else{
					switch (original->getPieceType()) {
					case KING: 
						if (original->isWhite()) {
							b->setPieceAt(s.x, s.y, new Pawn(false)); 
						}else {
							b->setPieceAt(s.x, s.y, nullptr);
						}
						break;
					case QUEEN: b->setPieceAt(s.x, s.y, new King(original->isWhite())); break;
					case BISHOP: b->setPieceAt(s.x, s.y, new Queen(original->isWhite())); break;
					case KNIGHT: b->setPieceAt(s.x, s.y, new Bishop(original->isWhite())); break;
					case ROOK: b->setPieceAt(s.x, s.y, new Knight(original->isWhite())); break;
					case PAWN: b->setPieceAt(s.x, s.y, new Rook(original->isWhite())); break;
					}
				}
			}else {
				//in a game
			}
		}
	}catch (int err) {
		//OOB
	}
}
void InPlayMenu::draw(SDL_Renderer* r) {
	//inPlayMenu should be entirely responsible for drawing the pieces
	SDL_RenderCopy(r, Menu::bg, NULL, NULL); //background first

	if (b) {
		for (int x = 0; x < b->getWidth(); x++) {
			for (int y = 0; y < b->getHeight(); y++) {
				Piece* pc = b->getPieceAt(x, y);
				if (pc) {
					//choose shape
					PieceType bah = pc->getPieceType();
					pieceRect.x = bah * 65;

					//choose color
					if (pc->isWhite()) {
						pieceRect.y = 0;
					}else {
						pieceRect.y = 65;
					}

					//choose where to stamp
					if (!flipped) {
						pieceRectStamper.x = x * 65;
						pieceRectStamper.y = y * 65;
					}else {
						SDL_Point n = flipPoint({x,y});
						pieceRectStamper.x = n.x * 65;
						pieceRectStamper.y = n.y * 65;
					}
					
					SDL_RenderCopy(r,pieceSprites,&pieceRect,&pieceRectStamper);

				}
			}
		}
		if (holding) {
			//highlights
		}
	}
}


void InPlayMenu::setFlipped(bool f) {
	flipped = f;
}
bool InPlayMenu::getFlipped() {
	return flipped;
}
void InPlayMenu::setBoard(Board* bn) {
	b = bn;
}
Board* InPlayMenu::getBoard() {
	return b;
}

SDL_Point InPlayMenu::flipPoint(SDL_Point p) {
	if (b) {
		SDL_Point toReturn;
		toReturn = {0-p.x+b->getWidth()-1,0-p.y+b->getHeight()-1};
		return toReturn;
	}else {
		return p;
	}
}