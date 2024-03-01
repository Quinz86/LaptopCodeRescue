#include <vector>
#include <stack>
#include <iostream>
#include <string>

#include "Board.h"

Board* createNewBoard(Board* s, int l, int n, int deltaL, int deltaN) {
	if (s->getPegAt(l + deltaL, n + deltaN) && !s->getPegAt(l + 2 * deltaL, n + 2 * deltaN)) {
		Board* ss = new Board(s);

		ss->setPegAt(l, n, false); //remove original 
		ss->setPegAt(l + deltaL, n + deltaN, false); //remove jumped
		ss->setPegAt(l + 2 * deltaL, n + 2 * deltaN, true);  //add landed

		ss->addMove({ l,n,l + 2 * deltaL, n + 2 * deltaN });
		return ss;
	}
	throw std::out_of_range("Not a valid move");
}

int main(int argc, char ** argv) {
	std::cout << "Begin" << std::endl;

	std::stack<Board*> toSearch = std::stack<Board*>();
	std::vector<Board*> won = std::vector<Board*>();

	toSearch.push(new Board());

	std::cout << "Calculating" << std::endl;
	while (!toSearch.empty()) {
		Board* s = toSearch.top();
		toSearch.pop();
		// do stuff with the s
		
		std::cout << s->toString();
		if (s->getNumPegsLeft() == 1) {
			won.push_back(s);
			std::cout << "SOLUTION FOUND!" << std::endl << std::endl;
			continue; //skips the s delete
		}
		std::cout << std::endl;

		for (int l = 1; l <= 5; l++) {
			for (int n = 1; n <= l; n++) {
				
				if (s->getPegAt(l,n)) {
					try {
						toSearch.push(createNewBoard(s,l,n, -1, 0));
					}catch (std::out_of_range e) {}
					try {
						toSearch.push(createNewBoard(s,l,n, -1,-1));
					}
					catch (std::out_of_range e) {}
					try {
						toSearch.push(createNewBoard(s,l,n,  0,-1));
					}
					catch (std::out_of_range e) {}
					try {
						toSearch.push(createNewBoard(s,l,n,  0, 1));
					}
					catch (std::out_of_range e) {}
					try {
						toSearch.push(createNewBoard(s,l,n,  1, 0));
					}
					catch (std::out_of_range e) {}
					try {
						toSearch.push(createNewBoard(s,l,n,  1, 1));
					}
					catch (std::out_of_range e) {}

					/* directions
					l-1 n		l-2 n
					l-1 n-1		l-2 n-2
					l   n-1		l   n-2
					l   n+1     l   n+2
					l+1 n       l+2 n
					l+1 n+1		l+2 n+2
					*/

				} //end of a single peg
				
			}
		} // end of all spots
		

		//ending for a board
		delete s;

	} // end while loop, ideally weve found all the winners
	std::cout << "Done" << std::endl;

	for (int b = 0; b < won.size(); b++) {
		std::cout << std::to_string(b+1) + ":\n" + won.at(b)->toString();
		std::vector<Move>* previousMoves = won.at(b)->getPreviousMoves();
		for (int m = 0; m < previousMoves->size(); m++) {
			std::cout << (std::to_string(previousMoves->at(m).il) + "," + std::to_string(previousMoves->at(m).in) + "->" + std::to_string(previousMoves->at(m).fl) + "," + std::to_string(previousMoves->at(m).fn) + "\n") ;
		}
		std::cout << std::endl;
		delete won.at(b);
	}

	/*
	std::cout << "hello world" << std::endl;
	for (int x = 0; x <= 10; x++) {
		std::cout << (std::to_string(x)  + ": " + std::to_string(Board::getNthTriangularNumber(x))) << std::endl;
	}
	*/
	std::string enter;
	std::cin >> enter;

	return 0;
}

