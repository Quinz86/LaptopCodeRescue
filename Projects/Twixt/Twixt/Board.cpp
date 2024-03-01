
#include "Board.h"
#include "CompareSDLPoints.h"
#include "SegmentIntersection.h"
#include <algorithm>


void Board::addPeg(SDL_Point pt, bool c) { //true = red, false = black
	Peg& temp = grid[pt.x][pt.y];
	temp.color = c;
	temp.active = true;
	temp.connections = 0;
}
void Board::removePeg(SDL_Point pt) {
	Peg& temp = grid[pt.x][pt.y];
	temp.active = false;

	//also need to remove connections
	removeConnection(pt, { pt.x+1, pt.y-2 });
	removeConnection(pt, { pt.x+2, pt.y-1 });
	removeConnection(pt, { pt.x+2, pt.y+1 });
	removeConnection(pt, { pt.x+1, pt.y+2 });
	removeConnection(pt, { pt.x-1, pt.y+2 });
	removeConnection(pt, { pt.x-2, pt.y+1 });
	removeConnection(pt, { pt.x-2, pt.y-1 });
	removeConnection(pt, { pt.x-1, pt.y-2 });

	temp.connections = 0; //just to be safe
}


void Board::removeConnection(SDL_Point pt1, SDL_Point pt2) {
	if (pointIsInBounds(pt1)) {
		unsigned char conDir = getDirectionFromPoint(pt1, pt2);
		if (conDir < 8) {
			grid[pt1.x][pt1.y].setConnection(conDir, false);
			if (pointIsInBounds(pt2)) {
				grid[pt2.x][pt2.y].setConnection((conDir+4)%8, false);
			}
		}
	}
}
void Board::createConnection(SDL_Point pt1, SDL_Point pt2) {
	if (pointIsInBounds(pt1) && pointIsInBounds(pt2)) {
		unsigned char conDir = getDirectionFromPoint(pt1, pt2);
		if (conDir < 8) {
			grid[pt1.x][pt1.y].setConnection(conDir, true);
			grid[pt2.x][pt2.y].setConnection((conDir + 4) % 8, true);
		}
	}
}
bool Board::flipConnection(SDL_Point pt1, SDL_Point pt2) {
	if (pointIsInBounds(pt1) && pointIsInBounds(pt2)) {
		unsigned char conDir = getDirectionFromPoint(pt1, pt2);
		if (conDir < 8 && !isBlocked(pt1,pt2)) {
			bool state = grid[pt1.x][pt1.y].getConnection(conDir);
			grid[pt1.x][pt1.y].setConnection(conDir, !state);
			grid[pt2.x][pt2.y].setConnection((conDir + 4) % 8, !state);
			return true;
		}
	}
	return false;
}

//warning might return 8
unsigned char Board::getDirectionFromPoint(SDL_Point source, SDL_Point other) {
	unsigned char conDir = 8;

	SDL_Point difference = {source.x-other.x, source.y-other.y};
	if        (difference.x == -1 && difference.y ==  2) {	conDir=0;
	} else if (difference.x == -2 && difference.y ==  1) {	conDir=1;
	} else if (difference.x == -2 && difference.y == -1) {	conDir=2;
	} else if (difference.x == -1 && difference.y == -2) {	conDir=3;
	} else if (difference.x ==  1 && difference.y == -2) {	conDir=4;
	} else if (difference.x ==  2 && difference.y == -1) {	conDir=5;
	} else if (difference.x ==  2 && difference.y ==  1) {	conDir=6;
	} else if (difference.x ==  1 && difference.y ==  2) {	conDir=7;
	} else {
		conDir = 8; //not a valid connection
	}

	return conDir;
}
SDL_Point Board::getPointFromDirection(SDL_Point source, unsigned char conDir) {
	SDL_Point other = {source.x,source.y};

	switch (conDir) {
	case 0: other.x +=  1; other.y += -2; break;
	case 1: other.x +=  2; other.y += -1; break;
	case 2: other.x +=  2; other.y +=  1; break;
	case 3: other.x +=  1; other.y +=  2; break;
	case 4: other.x += -1; other.y +=  2; break;
	case 5: other.x += -2; other.y +=  1; break;
	case 6: other.x += -2; other.y += -1; break;
	case 7: other.x += -1; other.y += -2; break;
	}

	return other;
}



bool Board::pointIsInBounds(SDL_Point pt){
	return (pt.x >= 0 && pt.x < 24 && pt.y >= 0 && pt.y < 24);
}

void Board::wipeCounted() {
	for (int x = 0; x < 24; x++) {
		for (int y = 0; y < 24; y++) {
			grid[x][y].counted = false;
		}
	}
}
bool Board::isBlocked(SDL_Point pt1, SDL_Point pt2) {
	for (int x = (std::min)(pt1.x, pt2.x); x <= (std::max)(pt1.x, pt2.x); x++) {
		for (int y = (std::min)(pt1.y, pt2.y); y <= (std::max)(pt1.y, pt2.y); y++) {
			if ((x == pt1.x && y == pt1.y) || (x == pt2.x && y == pt2.y)) {
				continue;
			}
			if (grid[x][y].active) {
				SDL_Point pt3 = { x,y };
				for (int d = 0; d < 8; d++) {
					if (grid[x][y].getConnection(d)) {
						SDL_Point pt4 = getPointFromDirection(pt3, d);
						if (doIntersect(pt1, pt2, pt3, pt4)) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
