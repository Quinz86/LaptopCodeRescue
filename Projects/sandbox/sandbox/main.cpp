#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

using namespace std;
namespace fs = std::experimental::filesystem;

int main()
{
	string dir = "AIs/";

	/*
	for (auto & p : fs::directory_iterator(dir)){
		string path = p.path().filename().string();
		std::cout << path << " said:" << std::endl;
		int written;

		fstream myFile;
		myFile.open(dir + path, ios::in | ios::binary);
		myFile.read((char*)&written, sizeof(int));
		

		cout << written << endl;
		myFile.close();

	}
	std::cout << "\nthis is last" << std::endl;
	std::string myString;
	std::cin >> myString;
	*/

//=============================================
	/*
	int whatIWrote;

	fstream myFile;
	myFile.open("binbin.dat", ios::in | ios::out | ios::binary);

	myFile.read((char*)&whatIWrote, sizeof(int));

	cout << whatIWrote << endl;
	string myString;
	cin >> myString;

	myFile.close();
	*/




//==============================================

	
	

	fstream myFile;
	myFile.open(dir + "toMake.dat", ios::out | ios::binary | fstream::out);

	int write1 = 100;
	myFile.write((char*)&write1, sizeof(int));
	write1 = 100;
	myFile.write((char*)&write1, sizeof(int));
	write1 = 25;
	myFile.write((char*)&write1, sizeof(int));
	write1 = 50;
	myFile.write((char*)&write1, sizeof(int));

	write1 = 0;
	myFile.write((char*)&write1, sizeof(int));
	write1 = 254;
	myFile.write((char*)&write1, sizeof(int));
	write1 = 0;
	myFile.write((char*)&write1, sizeof(int));
	

	

	
	myFile.close();
	
}