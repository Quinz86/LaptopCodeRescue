#pragma once
#include "Renderable.h"
#include <string>
#include "Clickable.h"
#include "WordBox.h"



class Button : public Renderable, public Clickable {
public:
	Button(std::string disp, int x, int y, int w, int h, int cN);
	~Button();

	void render(SDL_Renderer* r);
	int click(SDL_Point* point);
	SDL_Rect* getClickBox();

	static void setUp();
private:
	static SDL_Texture* sprite;

	int clickNum;
	WordBox* display = nullptr;
};
