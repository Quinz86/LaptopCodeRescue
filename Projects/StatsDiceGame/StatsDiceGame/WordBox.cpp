#include "WordBox.h"
#include "TextureManager.h"


//static
SDL_Texture* WordBox::letterSprites = nullptr;
SDL_Rect WordBox::letterSelectorBox = { 0,0,10,15 };
SDL_Rect WordBox::letterStamper = { 0,0,10,15 };
std::string WordBox::letterList = "ABCDEFabcdefGHIJKLghijklMNOPQRmnopqrSTUVWXstuvwxYZyz -~'\":()[].!?^<>,|/\\1234567890+=@#$%&*_`;";
void WordBox::setUp() {
	letterSprites = TextureManager::myTextureGet("font.png");
}
void WordBox::moveLetterSelectorBox(char c) {
	int x = 11;
	int y = 7;

	switch (c) {
	case 'A': x = 0; y = 0; break;
	case 'B': x = 1; y = 0; break;
	case 'C': x = 2; y = 0; break;
	case 'D': x = 3; y = 0; break;
	case 'E': x = 4; y = 0; break;
	case 'F': x = 5; y = 0; break;
	case 'G': x = 0; y = 1; break;
	case 'H': x = 1; y = 1; break;
	case 'I': x = 2; y = 1; break;
	case 'J': x = 3; y = 1; break;
	case 'K': x = 4; y = 1; break;
	case 'L': x = 5; y = 1; break;
	case 'M': x = 0; y = 2; break;
	case 'N': x = 1; y = 2; break;
	case 'O': x = 2; y = 2; break;
	case 'P': x = 3; y = 2; break;
	case 'Q': x = 4; y = 2; break;
	case 'R': x = 5; y = 2; break;
	case 'S': x = 0; y = 3; break;
	case 'T': x = 1; y = 3; break;
	case 'U': x = 2; y = 3; break;
	case 'V': x = 3; y = 3; break;
	case 'W': x = 4; y = 3; break;
	case 'X': x = 5; y = 3; break;
	case 'Y': x = 0; y = 4; break;
	case 'Z': x = 1; y = 4; break;
	case '1': x = 0; y = 6; break;
	case '2': x = 1; y = 6; break;
	case '3': x = 2; y = 6; break;
	case '4': x = 3; y = 6; break;
	case '5': x = 4; y = 6; break;
	case '6': x = 5; y = 6; break;
	case '7': x = 6; y = 6; break;
	case '8': x = 7; y = 6; break;
	case '9': x = 8; y = 6; break;
	case '0': x = 9; y = 6; break;
	case '*': x = 5; y = 7; break;
	case ' ': x = 4; y = 4; break;
	case '$': x = 2; y = 7; break;
	case '.': x = 2; y = 5; break;
	case '-': x = 5; y = 4; break;
	case ':': x = 9; y = 4; break;
	}
	x *= 10;
	y *= 15;
	letterSelectorBox = { x,y,10,15 };
}
void WordBox::moveLetterStamper(int x, int y, int w, int h) {
	letterStamper = { x,y,w,h };
}


//constructor
WordBox::WordBox(int x, int y, int w, int h, std::string disp) : Renderable(x,y,w,h){
	display = disp;
}
WordBox::~WordBox() {

}

//inherited
void WordBox::render(SDL_Renderer* r) {
	int letterWidth = getRect()->h * 2.0 / 3.0;//(getRect()->w) / display.length();
	int letterHeight = getRect()->h;

	for (int k = 0; k < display.length(); k++) {
		moveLetterStamper((getRect()->x)+(k*letterWidth),getRect()->y,letterWidth,letterHeight);
		moveLetterSelectorBox(display.at(k));
		SDL_RenderCopy(r, letterSprites, &letterSelectorBox, &letterStamper);
	}
}

//methods
void WordBox::changeWords(std::string s) {
	display = s;
}