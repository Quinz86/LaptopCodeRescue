#include "Chunk.h"
#include <stdlib.h>
#include "Island.h"

//constructor
Chunk::Chunk() {
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			grid[x][y] = new Tile(something something something something material= 0);
		}
	}
}
Chunk::Chunk(Island* i) {
	int spawnLandGrid[CHUNK_SIZE][CHUNK_SIZE];

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			spawnLandGrid[x][y] = rand()%2;
		}
	}
	
}
void Chunk::smooth() {
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			int totalLand = 0;
			if (i) { totalLand++; }
			if () { totalLand++; }
			if () { totalLand++; }
			if () { totalLand++; }
			if () { totalLand++; }
			if () { totalLand++; }
			if () { totalLand++; }
			if () { totalLand++; }

			if (totalLand >= 5) {
				spawnLandGrid[x][y] = 1;
			}
			else {
				spawnLandGrid[x][y] = 0;
			}
		}
	}
}
bool Chunk::getYesOrNo(Island* i, int x, int y) {

}
