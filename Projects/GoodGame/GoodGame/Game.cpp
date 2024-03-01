#include "Game.h"
#include "TextureManager.h"
#include "Character.h"
#include "Chunk.h"


//statics
SDL_Window* Game::MAINwindow = nullptr;
SDL_Renderer* Game::MAINrenderer = nullptr;
bool Game::done = false;
SDL_Point Game::mouseLocation = {0,0};
SDL_Rect Game::screenLocation = { 0,0,0,0 };
double Game::zoomLevel = 1;


std::vector<Clickable*> Game::clickables = std::vector<Clickable*>();
std::vector<Updatable*> Game::updatables = std::vector<Updatable*>();
MyOrderedList<Renderable*> Game::renderables = MyOrderedList<Renderable*>(Renderable::compHeights);

Character* Game::mainCharacter = nullptr;
Character* Game::sideCharacter = nullptr;
Chunk* Game::floor1 = nullptr;



//setup and cleanup
void Game::setup() {

	MAINwindow = SDL_CreateWindow("GoodGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		1300, 700,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	MAINrenderer = SDL_CreateRenderer(MAINwindow, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 20, 20, 50, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);
	
	int sw, sh;
	SDL_GetWindowSize(MAINwindow, &sw, &sh);
	screenLocation = { 0,0,sw,sh };

	done = false;
	mouseLocation = { 0,0 };


	TextureManager::setup(MAINrenderer);

	Chunk::setup(TextureManager::myTextureGet("IslandTiles/TileNESW.png"));
	//Chunk::setup(TextureManager::myTextureGet("DefaultTexture.png"));


	//<temporary testing grounds>

	mainCharacter = new Character(TextureManager::myTextureGet("imaspacecowboy.png"),    100,100,100,100);
	sideCharacter = new Character(TextureManager::myTextureGet("imaspacecowboy.png"), 100, 100, 100, 100);
	floor1 = new Chunk(0, 0);



	renderables.addInSequence(mainCharacter);
	updatables.push_back(mainCharacter);

	//<\temporary testing grounds>
}
void Game::run() {

	SDL_Event event;
	//begin game loop
	while (!done) {

		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: done = true; break;
					case SDLK_RIGHT: mainCharacter->addToVelocity(1, 0); break;
					case SDLK_LEFT: mainCharacter->addToVelocity(-1, 0); break;
					case SDLK_UP: mainCharacter->addToVelocity(0, -1); break;
					case SDLK_DOWN: mainCharacter->addToVelocity(0, 1); break;
					}
				}; break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT: mainCharacter->addToVelocity(-1, 0); break;
				case SDLK_LEFT: mainCharacter->addToVelocity(1, 0); break;
				case SDLK_UP: mainCharacter->addToVelocity(0, 1); break;
				case SDLK_DOWN: mainCharacter->addToVelocity(0, -1); break;
				}
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) { // left click
					for (int x = 0; x < clickables.size(); x++) {
						if (SDL_PointInRect(&mouseLocation,clickables.at(x)->getClickBox()) ) {
							handleClickNum(clickables.at(x)->click(&mouseLocation));
							break; //comment this out to click both overlapping things
						}
					}
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) { // right click

				}; break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y };
				break;
			}

		}

		//begin updating
		for (int x = 0; x < updatables.size(); x++) {
			updatables.at(x)->update();
		}
		SDL_Rect* tempFocusRect = mainCharacter->getRect();
		setScreenFocus(tempFocusRect->x+tempFocusRect->w/2,tempFocusRect->y+tempFocusRect->h/2);

		//begin rendering
		for (auto it = renderables.getIteratorStart(); it != renderables.getIteratorEnd(); it++){
			(*it)->render(MAINrenderer);
		}
		

		SDL_RenderPresent(MAINrenderer);
	}
}
void Game::cleanup() {
	TextureManager::cleanup();
	delete mainCharacter;

	delete sideCharacter;
	delete floor1;
}
//end setup and cleanup


//returns the ORIGIN of the screen
SDL_Rect* Game::getScreenLocation() {
	return &screenLocation;
}
double Game::getZoomLevel() {
	return zoomLevel;
}










void Game::handleClickNum(int num) {
	switch (num) {
	case 1: break;
	}
}
//sets the CENTER of the screen
void Game::setScreenFocus(int x, int y) {
	screenLocation.x = x - screenLocation.w / 2;
	screenLocation.y = y - screenLocation.h / 2;
}