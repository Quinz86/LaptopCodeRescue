#include "Game.h"
#include "Button.h"
#include "SDL_image.h"
#include <iostream>
#include "Menu.h"
#include <fstream>
#include "InPlayMenu.h"
#include "Board.h"
#include "AllThePieces.h"

#define FLIPPER_MAX 2048

//static
std::string Game::letterList = "ABCDEFabcdef"
							   "GHIJKLghijkl"
							   "MNOPQRmnopqr"
							   "STUVWXstuvwx"
							   "YZyz -~'\":()"
							   "[].!?^<>,|/\\"
							   "1234567890+="
							   "@#$%&*_`;";
SDL_Rect Game::letterSelector = { 0,0,10,15 };
SDL_Rect Game::letterStamper = { 1,1,1,1 };

SDL_Texture* Game::logo = nullptr;
SDL_Texture* Game::font = nullptr;

std::vector<Menu*> Game::states = std::vector<Menu*>();
Button* Game::fileChooser = nullptr;
Button* Game::nameMaker = nullptr;

void Game::setup(SDL_Texture* l, SDL_Texture* f) {
	logo = l;
	font = f;


	//makin all the menus, and teh buttons
	Button* bb;
	Menu* mm;

	//0
	mm = new Menu(); // main menu
	bb = new Button(0, { 325,390,130,65 }, "Quit", true); mm->addButton(bb); //exit
	bb = new Button(1, { 65 ,390,195,65 }, "Options", true); mm->addButton(bb); //open options menu
	bb = new Button(2, { 65 ,260,130,65 }, "New", true); mm->addButton(bb); //open new game menu
	bb = new Button(3, { 260,260,195,65 }, "Play!", true); mm->addButton(bb); //open play menu
	states.push_back(mm);

	//1
	mm = new Menu(); // new game menu
	bb = new Button(4, { 0, 65*7, 65*2, 65 }, "Back", true); mm->addButton(bb); // 4 = back to main menu
	bb = new Button(5, { 65*6, 65*7, 65*2, 65 }, "OK!", true); mm->addButton(bb); //create board file
	bb = new Button(6, { 65, 65*5, 65*5, 65 },"Edit Pieces",true); mm->addButton(bb);
	bb = new Button(-1,{ 65*3, 65*3, 65*2, 65 }, "by", false); mm->addButton(bb); // "by" display only
	bb = new Button(7, { 65, 65, 65 * 6, 65 }, "[Name]", true); mm->addButton(bb); nameMaker = bb;// 7 = edit this buttons display
	bb = new Button(7, { 65, 65*3, 65, 65 }, "8", false); mm->addButton(bb);// 7 = edit this buttons display
	bb = new Button(7, { 65*6, 65*3, 65, 65 }, "8", false); mm->addButton(bb);// 7 = edit this buttons display
	states.push_back(mm);

	//2
	mm = new Menu(); //play menu
	bb = new Button(4, { 0, 65 * 7, 65 * 2, 65 }, "Back", true); mm->addButton(bb);   //back to main menu
	bb = new Button(8, { 65,65,65*6,65 }, "Offline Mode", true); mm->addButton(bb); //offline mode menu
	bb = new Button(9, { 65,65*3,65 * 2,65 }, "Host", true); mm->addButton(bb);    //host menu
	bb = new Button(10, { 65*5,65*3,65 * 2,65 }, "Join", true); mm->addButton(bb);    //join menu
	states.push_back(mm);

	//3
	mm = new InPlayMenu(true); // board edit menu
	//((InPlayMenu*)mm)->setBoard(new Board());    //this is done when clicking "new!"
	states.push_back(mm);
}

//constructor
Game::Game(SDL_Renderer* rend){
	r = rend;
	gameState = 0;
	mouseLocation = { 0,0 };
	done = false;
	typing = nullptr;
	shift = false;
	singlePlayer = true;

}
Game::~Game() {
	for (int x = 0; x < states.size(); x++) {
		delete states.at(x);
	}
}

void Game::run()
{
	
	SDL_Rect logoRect = { 0,65,65 * 8,65 * 2 };

	SDL_Event event;
	int flipper = 0;

	//begin game loop
	while (!done) {
		//begin event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break; 
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y };
				states.at(gameState)->mouseMoved(&mouseLocation);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) { // left click
					typing = nullptr;
					states.at(gameState)->click(&mouseLocation);
				}else if (event.button.button == SDL_BUTTON_RIGHT) { // right click
					if (gameState == 3) {
						gameState = 1; //exit eint x, int y, int w, int hdit mode
						//NOT RESETTING EDIT BOARD HERE
					}else if (gameState == 900) {
									   //engage pause menu
					}
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					if (event.key.keysym.sym == SDLK_ESCAPE) { done = true; }    // #dont# could make this different if in different game state by calling buttonReaction appropriately (with nullptr as button pointer)
					else if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) { shift = true; }
					else if (typing) {
						switch (event.key.keysym.sym) {
						case SDLK_BACKSPACE: typing->setDisplay(typing->getDisplay().substr(0, typing->getDisplay().length() - 1)); break;
						case SDLK_SPACE: typing->setDisplay(typing->getDisplay() + " "); break;
						case SDLK_a: typing->setDisplay(typing->getDisplay() + "a"); break;
						case SDLK_b: typing->setDisplay(typing->getDisplay() + "b"); break;
						case SDLK_c: typing->setDisplay(typing->getDisplay() + "c"); break;
						case SDLK_d: typing->setDisplay(typing->getDisplay() + "d"); break;
						case SDLK_e: typing->setDisplay(typing->getDisplay() + "e"); break;
						case SDLK_f: typing->setDisplay(typing->getDisplay() + "f"); break;
						case SDLK_g: typing->setDisplay(typing->getDisplay() + "g"); break;
						case SDLK_h: typing->setDisplay(typing->getDisplay() + "h"); break;
						case SDLK_i: typing->setDisplay(typing->getDisplay() + "i"); break;
						case SDLK_j: typing->setDisplay(typing->getDisplay() + "j"); break;
						case SDLK_k: typing->setDisplay(typing->getDisplay() + "k"); break;
						case SDLK_l: typing->setDisplay(typing->getDisplay() + "l"); break;
						case SDLK_m: typing->setDisplay(typing->getDisplay() + "m"); break;
						case SDLK_n: typing->setDisplay(typing->getDisplay() + "n"); break;
						case SDLK_o: typing->setDisplay(typing->getDisplay() + "o"); break;
						case SDLK_p: typing->setDisplay(typing->getDisplay() + "p"); break;
						case SDLK_q: typing->setDisplay(typing->getDisplay() + "q"); break;
						case SDLK_r: typing->setDisplay(typing->getDisplay() + "r"); break;
						case SDLK_s: typing->setDisplay(typing->getDisplay() + "s"); break;
						case SDLK_t: typing->setDisplay(typing->getDisplay() + "t"); break;
						case SDLK_u: typing->setDisplay(typing->getDisplay() + "u"); break;
						case SDLK_v: typing->setDisplay(typing->getDisplay() + "v"); break;
						case SDLK_w: typing->setDisplay(typing->getDisplay() + "w"); break;
						case SDLK_x: typing->setDisplay(typing->getDisplay() + "x"); break;
						case SDLK_y: typing->setDisplay(typing->getDisplay() + "y"); break;
						case SDLK_z: typing->setDisplay(typing->getDisplay() + "z"); break;
						case SDLK_0: typing->setDisplay(typing->getDisplay() + "0"); break;
						case SDLK_1: typing->setDisplay(typing->getDisplay() + "1"); break;
						case SDLK_2: typing->setDisplay(typing->getDisplay() + "2"); break;
						case SDLK_3: typing->setDisplay(typing->getDisplay() + "3"); break;
						case SDLK_4: typing->setDisplay(typing->getDisplay() + "4"); break;
						case SDLK_5: typing->setDisplay(typing->getDisplay() + "5"); break;
						case SDLK_6: typing->setDisplay(typing->getDisplay() + "6"); break;
						case SDLK_7: typing->setDisplay(typing->getDisplay() + "7"); break;
						case SDLK_8: typing->setDisplay(typing->getDisplay() + "8"); break;
						case SDLK_9: typing->setDisplay(typing->getDisplay() + "9"); break;
						default: break;
						}
					}
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {shift = false;}
				break;
			}
		}
		//end event handling



		states.at(gameState)->draw(r);
		if (gameState == 0) {
			SDL_RenderCopy(r, logo, NULL, &logoRect); //logo
		}

		SDL_RenderPresent(r);
		//std::cout << mouseLocation.x  << std::endl;

		flipper++;
		if (flipper >= FLIPPER_MAX) { flipper = 0; }
	}
	//end game loop
	
}
void Game::buttonReaction(int n, Button* from) {
	switch (n) {
	case 0: done = true; break;
	case 1: std::cout << "you clicked options" << std::endl; break;  //open options menu
	case 2:															 //open new game menu
		gameState = 1; 
		delete ((InPlayMenu*)states.at(3))->getBoard();
		((InPlayMenu*)states.at(3))->setBoard(new Board());  ///yes resetting edit baord here
		nameMaker->setDisplay("[Name]");
		break;									 
	case 3: gameState = 2; break;									 //open play menu
	case 4: gameState = 0; break;									 //back to main menu
	case 5: 															 //create board file
		{	
		std::string nam = "Games/"+ nameMaker->getDisplay() + ".mtch";
		
		std::fstream fileTest = std::fstream();
		fileTest.open(nam, std::ios::out | std::ios::binary | std::ios::trunc);
		int foo = 8;
		bool bar = true;
		fileTest.write((char*)&foo, sizeof(int));
		fileTest.write((char*)&foo, sizeof(int));
		fileTest.write((char*)&bar, sizeof(bool));
		fileTest.close(); 

		((InPlayMenu*)states.at(3))->getBoard()->writePieces(nam);
		}

		//from->setClickable(false); 
		gameState = 2; //go to play menu
		break;
	case 6: gameState = 3; break;									 //edit pieces
	case 7: typing = from; break;									 //edit button display
	case 8: 
		singlePlayer = true;
		break;
	case 9: 
		singlePlayer = false;
		break;
	case 10:
		singlePlayer = false;
		break;

	default: std::cout << "unlinked button" << std::endl; break; //do nothing
	}
}






void Game::drawWords(SDL_Rect* wordBox, std::string words) {
	if (words.length() == 0) { return; }

	letterStamper.x = wordBox->x;
	letterStamper.y = wordBox->y;
	//double ratio = wordBox->h / letterStamper.h;
	letterStamper.h = wordBox->h;
	letterStamper.w = wordBox->w / words.length();  // idk look into this more

	for (int a = 0; a < words.length(); a++) {
		char c = words.at(a);
		int b;
		for (b = 0; b < letterList.length(); b++) {
			if (c == letterList.at(b)) {
				break;
			}
		}
		if (b >= letterList.length()) {
			b = 95;
		}
		letterSelector.y = (b / 12) * 15;
		letterSelector.x = (b % 12) * 10;
		
		SDL_RenderCopy(r, font, &letterSelector, &letterStamper);
		
		letterStamper.x += letterStamper.w;

	}
}

bool Game::isSinglePlayer() {
	return singlePlayer;
}



