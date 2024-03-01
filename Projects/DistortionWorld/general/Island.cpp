#include "Island.h"
#include <stdlib.h>
#include "Chunk.h"
#include <ostream>

//static setup
/*Chunk* Island::emptyChunk = nullptr;
void Island::setupIsland() {
	emptyC
}*/
void Island::smooth(std::vector<std::vector<bool>>* grid) {
	for (int x = 0; x < grid->size(); x++) {
		for (int y = 0; y < grid->at(x).size(); y++) {
			
			int count = 0;
			for (int i = x-1; i <= x+1; i++) {
				for (int j = y-1; j <= y+1; j++) {
					if( !(i == x && j == y) &&
						i >= 0 && i < grid->size() &&
						j >= 0 && j < grid->at(i).size() ) {
							count += grid->at(i).at(j);
					}
				}
			}
			grid->at(x).at(y) = (count > 4);
		}
	}
}
void trim(std::vector<std::vector<bool>>* grid) {

}


Island::Island() {
	Island(rand()%MAX_ISLAND_LENGTH+1,rand()%MAX_ISLAND_LENGTH+1);
}
Island::Island(int w, int h) {
	//general island size
	std::vector<std::vector<bool>> chunkGrid = std::vector<std::vector<bool>>();
	for (int x = 0; x < w; x++) {
		chunkGrid.push_back(std::vector<bool>());
		for (int y = 0; y < h; y++) {
			chunkGrid.at(x).push_back((bool)(rand() % 2));	
		}
	}
	smooth(&chunkGrid);
	trim(&chunkGrid);

	std::vector<std::vector<bool>> fineGrid = std::vector<std::vector<bool>>();
	for (int x = 0; x < w*Chunk::CHUNK_SIZE; x++) {
		fineGrid.push_back(std::vector<bool>());
		for (int y = 0; y < h*Chunk::CHUNK_SIZE; y++) {
			tempGrid.at(x).push_back((bool)(rand()%2));
		}
	}




	grid = std::vector<std::vector<Chunk*>>();
	//delete chunkGrid; delete fineGrid; //it dies when the constructor ends yes, and all elements are deconstructed as well
}