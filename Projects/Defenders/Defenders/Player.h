#pragma once

class Player {
public:
	Player(int nx, int ny);
private:
	int x, y;
	int direction;
	const static int w = 10;
	const static int h = 10;
};