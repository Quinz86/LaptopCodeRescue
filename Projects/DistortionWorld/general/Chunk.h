#pragma once

class Tile;
class Island;
class Chunk {
public:
	static const int CHUNK_SIZE = 16;
	Chunk();
	Chunk(Island* i);
	~Chunk();


private:
	Tile* grid[CHUNK_SIZE][CHUNK_SIZE];
	bool getYesOrNo(Island* i, int horizontal, int vertical);
	void smooth();
};