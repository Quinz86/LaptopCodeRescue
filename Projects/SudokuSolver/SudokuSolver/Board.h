#pragma once




struct Board {
public:
	Board() {
		emptySpaces = 9*9;
		broken = false;
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				grid[x][y] = 0;
			}
		}
	}
	Board(char gd[9][9]) {
		emptySpaces = 0;
		broken = false;
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (gd[x][y] == 0) { emptySpaces++; }
				grid[x][y] = gd[x][y];
			}
		}
	}
	char grid[9][9];
	char emptySpaces;
	bool broken;
};