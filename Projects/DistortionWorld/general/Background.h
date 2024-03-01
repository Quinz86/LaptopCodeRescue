#pragma once
#include "Thing.h"
#include <string>

class Background : public Thing {
public:
	Background(std::string spriten, int x, int y, int w, int h, bool sw);
	~Background();

	void upd8();
	void blit_self();
private:
	SDL_Texture* sprite;
	bool scrollWith;
};