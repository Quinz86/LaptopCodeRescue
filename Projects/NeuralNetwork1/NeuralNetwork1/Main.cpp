#include <utility>
#include <time.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include "Network.h"
#define TEMP 0.5
#define numLAYERS 2

int main(int argc, char ** argv)
{
	srand(time(NULL));
	std::vector<std::string> trainingFiles; //this should only be about 2 or 3
	
	std::string dir = "training/";
	for (auto & p : std::experimental::filesystem::directory_iterator(dir)) {
		std::string path = p.path().filename().string();
		trainingFiles.push_back(path);
	}


	Network myNetwork = Network();


	std::string line;
	std::ifstream myfile;
	for (int x = 0; x < trainingFiles.size(); x++) {
		myfile.open(trainingFiles.at(x));
		if (myfile.is_open()) {
			//==========================
			while (getline(myfile, line)) {
				myNetwork.trainWith(line);
			}
			//==========================
		};
		myfile.close();
	}
		
	myNetwork.createData(TEMP);
		
	return 0;
}