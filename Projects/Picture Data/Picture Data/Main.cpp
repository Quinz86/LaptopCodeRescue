#include <fstream>
#include <iostream>
#include <string>





int main() {
	int toReturn;
	std::fstream myFile;

	myFile.open("Assets/smokey.png", std::fstream::binary | std::fstream::in);
	if (myFile.is_open()) {
		std::cout << "Read the contents:" << std::endl << std::endl;

		int count = 0;

		std::streampos size = myFile.tellg();
		char memblock;
		myFile.seekg(0, std::ios::beg);
		while (myFile.get(memblock)) {
			count++;
			std::cout << count << ": ";
			for (int i = 7; i >= 0; --i)
			{
				std::cout << ((memblock & (1 << i)) ? '1' : '0');
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;

		std::cout << "File has been read" << std::endl;

		
		/*
		for (int x = 0; x < size; x++) {
			std::cout << x << " " << memblock[x] << std::endl;
		}
		*/
		
		/*
		std::string line;
		while (std::getline(myFile, line))
		{
			std::cout << line << '\n';
		}
		*/

		std::cout << std::endl << std::endl;
		std::cout << "Complete" << std::endl;
		
		/*
		int * lmnop = new int[20];
		for (int x = 0; x < 20; x++) {
			lmnop[x] = x;
		}
		for (int x = 0; x < 20; x++) {
			std::cout << lmnop[x] << std::endl;
		}
		*/

		myFile.close();
		toReturn = 0;
	} else {
		toReturn = 1;
	}
	std::cout << toReturn << std::endl;
	int s1;
	std::cin >> s1;
	return toReturn;
}