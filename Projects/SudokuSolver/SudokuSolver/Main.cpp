
#include <stack>
#include <iostream>

#include "Board.h"

bool isBlocked(Board& b, char x, char y, char i) {
	if (b.grid[x][y] != 0) { return true; }

	//lines
	for (int h = 0; h < 9; h++) {
		if (b.grid[x][h] == i) {
			return true;
		}
	}
	//columns
	for (int k = 0; k < 9; k++) {
		if (b.grid[k][y] == i) {
			return true;
		}
	}
	//boxes
	char xn = x / 3;
	char yn = y / 3;
	for (int kn = 0; kn < 3; kn++) {
		for (int hn = 0; hn < 3; hn++) {
			if (b.grid[(xn * 3) + kn][(yn * 3) + hn] == i) {
				return true;
			}
		}
	}
	return false;
}


// returns true if a box was successfully filled in, false if a guess is needed
bool sequence(Board& b) {
	char px = 0;
	char py = 0;
	char availableSpots; //if 0, board is broken, or its a winner, so return false
	bool iFound;
	for (char i = 1; i <= 9; i++) {
		//lines
		for (int k = 0; k < 9; k++) {
			availableSpots = 0;
			iFound = false;
			for (int y = 0; y < 9; y++) {
				if (b.grid[k][y] == i) { iFound = true; break; }
				if (!isBlocked(b, k, y, i)) { availableSpots++; px = k; py = y; }
			}
			if (iFound) { continue; }
			if (availableSpots == 1) {
				b.grid[px][py] = i;
				b.emptySpaces--;
				return true;
			} else if (availableSpots == 0) {
				b.broken = true;
				return false;
			}
		}

		//columns
		for (int h = 0; h < 9; h++) {
			availableSpots = 0;
			iFound = false;
			for (int x = 0; x < 9; x++) {
				if (b.grid[x][h] == i) { iFound = true; break; }
				if (!isBlocked(b, x, h, i)) { availableSpots++; px = x; py = h; }
			}
			if (iFound) { continue; }
			if (availableSpots == 1) {
				b.grid[px][py] = i;
				b.emptySpaces--;
				return true;
			}
			else if (availableSpots == 0) {
				b.broken = true;
				return false;
			}
		}

		//boxes
		for (int xn = 0; xn < 3; xn++) {
			for(int yn = 0; yn < 3; yn++){
				availableSpots = 0;
				iFound = false;
				for (int kn = 0; kn < 3; kn++) {
					for (int hn = 0; hn < 3; hn++) {
						if (b.grid[(xn*3)+kn][(yn*3)+hn] == i) { iFound = true; break; }
						if (!isBlocked(b, (xn*3)+kn, (yn*3)+hn, i)) { availableSpots++; px = (xn*3)+kn; py = (yn*3)+hn; }
					}
					if (iFound) { break; }
				}
				if (iFound) { continue; }
				if (availableSpots == 1) {
					b.grid[px][py] = i;
					b.emptySpaces--;
					return true;
				} else if (availableSpots == 0) {
					b.broken = true;
					return false;
				}
			}
		}
	}

	return false;
}



void printWinner(Board& b) {
	//print winner
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			std::cout << (char)(b.grid[x][y]+48);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}




int main(int argc, char ** argv) {

	/*
	char startGrid[9][9] = {{ 0,6,8,0,5,0,0,7,0 },
	                        { 7,0,2,0,0,6,0,0,5 },
							{ 0,0,0,0,1,7,0,6,4 },
							{ 0,7,3,0,0,0,0,0,0 },
							{ 6,0,5,0,2,0,4,0,9 },
							{ 0,0,0,0,0,0,3,5,0 },
							{ 8,4,0,3,7,0,0,0,0 },
							{ 2,0,0,1,0,0,8,0,6 },
							{ 0,5,0,0,6,0,7,4,0 }};
	*/
	char startGrid[9][9] = {{ 0,0,5,9,0,0,0,6,3 },
	                        { 0,9,0,0,0,0,2,0,0 },
							{ 1,0,0,0,0,4,0,0,0 },
							{ 7,0,0,0,0,2,0,0,0 },
							{ 2,1,6,0,0,5,9,8,0 },
							{ 5,0,0,8,0,6,0,0,1 },
							{ 9,0,0,4,0,1,0,0,5 },
							{ 8,0,0,2,0,3,0,0,7 },
							{ 0,6,4,0,0,0,8,1,0 }};
	std::stack<Board> boards = std::stack<Board>();
	boards.push(Board(startGrid));

	printWinner(boards.top());

	while (!boards.empty()) {
		Board temp = boards.top();
		boards.pop();

		bool keepWorking = true;
		while (keepWorking) {
			keepWorking = sequence(temp);
			printWinner(temp);
		}
		if (temp.emptySpaces == 0) { printWinner(temp); break; }
		if (temp.broken) { continue; }
		//time to guess
		//add at least 2 guesses to stack
	}
	

}

