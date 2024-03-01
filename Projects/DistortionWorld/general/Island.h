#pragma once
#include <vector>

class Chunk;
class Island {
public:
	static const int MAX_ISLAND_LENGTH = 10;
	static void smooth(std::vector<std::vector<bool>>* grid);

	Island();
	Island(int w, int h);
	~Island();

	static const Chunk* emptyChunk;
	static void setupIsland();
private:
	std::vector<std::vector<Chunk*>> grid;

};