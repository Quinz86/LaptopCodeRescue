#pragma once
#include "Updatable.h"
#include "Renderable.h"
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "WordBox.h"

class Die : public Updatable, public Renderable {
public:
	Die(int nf, int x, int y, int w);
	~Die();

	void roll();
	int getNumFaces();
	int getShowNum();

	void update();
	void render(SDL_Renderer* r);

	static void setup();
private:
	static SDL_Rect animationSelectorBox;
	static void moveAnimationSelectorBox(int x, int y);
	static std::vector<int> sides4;
	static std::vector<int> sides6;

	SDL_Texture* myDisplayTexture;
	SDL_Texture* myAnimationTexture;

	int randomFace();

	int showNum = 0;
	int numFaces;
	int animationTimer = -1;
	

	WordBox* display = nullptr;
};