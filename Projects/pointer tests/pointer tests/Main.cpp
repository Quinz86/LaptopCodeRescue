#include <iostream>









int main(int argc, char ** argv) {


	int* n1 = new int(5);
	std::cout << n1 << std::endl;
	delete n1;

	int x;
	std::cin >> x;

	return 0;

}