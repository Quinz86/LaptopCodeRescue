#include "Die.h"
#include "TextureManager.h"



//static
SDL_Rect Die::animationSelectorBox = { 0,0,64,64 };
std::vector<int> Die::sides4 = std::vector<int>();
std::vector<int> Die::sides6 = std::vector<int>();
void Die::setup() {
	sides4.push_back(2);
	sides4.push_back(4);
	sides4.push_back(6);
	sides4.push_back(8);

	sides6.push_back(3);
	sides6.push_back(4);
	sides6.push_back(5);
	sides6.push_back(6);
	sides6.push_back(7);
	sides6.push_back(8);
}
void Die::moveAnimationSelectorBox(int x, int y) {
	animationSelectorBox = { x, y, 64, 64 };
}




//constructor
Die::Die(int nf, int x, int y, int w) : Updatable(), Renderable(x,y,w,w) {
	numFaces = nf;

	switch (numFaces){
	case 4: myDisplayTexture = TextureManager::myTextureGet("DiceTextures/D4.png"); myAnimationTexture = TextureManager::myTextureGet("DiceTextures/triangle roll animation.png"); break;
	case 6: myDisplayTexture = TextureManager::myTextureGet("DiceTextures/D6.png"); myAnimationTexture = TextureManager::myTextureGet("DiceTextures/square roll animation.png"); break;
	}

	display = new WordBox(x+(w/3),y+(w/4),w/3,w/2,"*");
}
Die::~Die() {
	delete display;
}

//methods
void Die::roll() {
	animationTimer = 0;
	showNum = 0;
}
int Die::getNumFaces() {
	return numFaces;
}
int Die::getShowNum() {
	return showNum;
}
int Die::randomFace() {
	int toReturn;
	switch (numFaces) {
	case 4: toReturn = sides4.at(rand() % sides4.size()); break;
	case 6: toReturn = sides6.at(rand() % sides6.size()); break;
	default: toReturn = 0;
	}
	return toReturn;
}

//inherited
void Die::update() {
	if (animationTimer >= 0) {
		animationTimer++;
	}
	if (animationTimer > 500) {
		animationTimer = -1;
		showNum = randomFace();
		display->changeWords(std::to_string(showNum));
	}
}
void Die::render(SDL_Renderer* r) {
	if (animationTimer == -1) {
		SDL_RenderCopy(r, myDisplayTexture, NULL, getRect());
		display->render(r);
	}else {
		moveAnimationSelectorBox((animationTimer%8)*64,0);
		SDL_RenderCopy(r, myAnimationTexture, &animationSelectorBox, getRect());
	}
}