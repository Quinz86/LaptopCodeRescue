#pragma once
#include <string>
#include "Renderable.h"

class WordBox : public Renderable {
public:
	WordBox(int x, int y, int w, int h, std::string disp);
	~WordBox();

	void changeWords(std::string s);

	void render(SDL_Renderer* r);

	static void setUp();
	
private:
	static SDL_Texture* letterSprites;
	static std::string letterList;

	static SDL_Rect letterSelectorBox;
	static void moveLetterSelectorBox(char c);
	static SDL_Rect letterStamper;
	static void moveLetterStamper(int x, int y, int w, int h);

	std::string display;

};