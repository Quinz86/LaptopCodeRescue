#include "Game.h"
#include "SDL_image.h"
#include <string>

//constructor
Game::Game(SDL_Renderer* mr) {
	r = mr;
	clicked = -1;
	selected = -1;
	currentQuestionNum = 0;
}
void Game::run() {
	setup();

	bool done = false;
	SDL_Event event;
	SDL_Rect letterDraw = { 0,0,25,25 };
	SDL_Rect letterTrace = { 0,0,25,25 };
	std::string letterList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.!?- :";
	std::string message;

	while (!done) {//begin gameloop
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: done = true; break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					switch (event.key.keysym.sym) {
					case SDLK_LEFT:  break;
					case SDLK_RIGHT:  break;
					case SDLK_DOWN:  break;
					case SDLK_UP:  break;
					case SDLK_ESCAPE: done = true; break;
					case SDLK_SPACE:	break;
					};
				}; break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:  break;
				case SDLK_RIGHT:  break;
				case SDLK_DOWN:  break;
				case SDLK_UP: break;
				}; break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y }; break;
			case SDL_MOUSEBUTTONDOWN:
				clicked = -1;
				for (int b = 0; b < buttons.size(); b++) {
					if (SDL_PointInRect(&mouseLocation, buttons[b]->getRectan())) {
						clicked = b;
					}
				}
				break;
			};
		};


		if (clicked != -1) { //clicked something
			int val = buttons[clicked]->click();
			switch (val) {
				case -1: if (selected != -1) { 
							selected = -1; 
							currentQuestionNum += 1;
							}break;  //next button pressed 
				case 0: selected = 0; break;
				case 1: selected = 1; break;
				case 2: selected = 2; break;
				case 3: selected = 3; break;
				case 4: selected = 4; break;
			};
			clicked = -1;
		}





		//blits
		SDL_RenderCopy(r, textures[0], NULL, NULL);
		if (selected != -1) {
			SDL_RenderCopy(r, textures[1], NULL, buttons[selected]->getRectan());
		}
		message = questions[currentQuestionNum].ask;
		for (int l = 0; l < message.size(); l++) {
			
			if       (message[l] == letterList[0])  { letterTrace.x = 0;   letterTrace.y = 0;
			}else if (message[l] == letterList[1])  { letterTrace.x = 25;  letterTrace.y = 0;
			}else if (message[l] == letterList[2])  { letterTrace.x = 50; letterTrace.y = 0;
			}else if (message[l] == letterList[3])  { letterTrace.x = 75; letterTrace.y = 0;
			}else if (message[l] == letterList[4])  { letterTrace.x = 100; letterTrace.y = 0;
			}else if (message[l] == letterList[5])  { letterTrace.x = 125; letterTrace.y = 0;
			}else if (message[l] == letterList[6])  { letterTrace.x = 150; letterTrace.y = 0;
			}else if (message[l] == letterList[7])  { letterTrace.x = 0;   letterTrace.y = 25;
			}else if (message[l] == letterList[8])  { letterTrace.x = 25;  letterTrace.y = 25;
			}else if (message[l] == letterList[9])  { letterTrace.x = 50; letterTrace.y = 25;
			}else if (message[l] == letterList[10]) { letterTrace.x = 75; letterTrace.y = 25;
			}else if (message[l] == letterList[11]) { letterTrace.x = 100; letterTrace.y = 25;
			}else if (message[l] == letterList[12]) { letterTrace.x = 125; letterTrace.y = 25;
			}else if (message[l] == letterList[13]) { letterTrace.x = 150; letterTrace.y = 25;
			}else if (message[l] == letterList[14]) { letterTrace.x = 0;   letterTrace.y = 50;
			}else if (message[l] == letterList[15]) { letterTrace.x = 25;  letterTrace.y = 50;
			}else if (message[l] == letterList[16]) { letterTrace.x = 50; letterTrace.y = 50;
			}else if (message[l] == letterList[17]) { letterTrace.x = 75; letterTrace.y = 50;
			}else if (message[l] == letterList[18]) { letterTrace.x = 100; letterTrace.y = 50;
			}else if (message[l] == letterList[19]) { letterTrace.x = 125; letterTrace.y = 50;
			}else if (message[l] == letterList[20]) { letterTrace.x = 150; letterTrace.y = 50;
			}else if (message[l] == letterList[21]) { letterTrace.x = 0;   letterTrace.y = 75;
			}else if (message[l] == letterList[22]) { letterTrace.x = 25;  letterTrace.y = 75;
			}else if (message[l] == letterList[23]) { letterTrace.x = 50; letterTrace.y = 75;
			}else if (message[l] == letterList[24]) { letterTrace.x = 75; letterTrace.y = 75;
			}else if (message[l] == letterList[25]) { letterTrace.x = 100; letterTrace.y = 75;

			}else if (message[l] == letterList[26]) { letterTrace.x = 125; letterTrace.y = 75;
			}else if (message[l] == letterList[27]) { letterTrace.x = 150; letterTrace.y = 75;
			}else if (message[l] == letterList[28]) { letterTrace.x = 0;   letterTrace.y = 100;
			}else if (message[l] == letterList[29]) { letterTrace.x = 25;  letterTrace.y = 100;
			}else if (message[l] == letterList[30]) { letterTrace.x = 50; letterTrace.y = 100;
			}else if (message[l] == letterList[31]) { letterTrace.x = 75; letterTrace.y = 100;
			}else if (message[l] == letterList[32]) { letterTrace.x = 100; letterTrace.y = 100;}

			letterDraw.x = 15+ (l%18)*25; //435 
			letterDraw.y = 25+ (l/18)*28;
			SDL_RenderCopy(r, textures[2], &letterTrace, &letterDraw);
		}
		SDL_RenderCopy(r, textures[3], NULL, buttons[5]->getRectan()); //i dont know why this is here, just add it to the bg texture



		SDL_RenderPresent(r);
		SDL_Delay(5);
	};//end gameloop 
	
	cleanup();
};

//setup and cleanup
void Game::setup() {
	//textures
	SDL_Surface* surf = IMG_Load("sprites/background.png");
	SDL_Texture* BGTexture = SDL_CreateTextureFromSurface(r, surf);
	textures.push_back(BGTexture);
	surf = IMG_Load("sprites/selector.png");
	SDL_Texture* NSTexture = SDL_CreateTextureFromSurface(r, surf);
	textures.push_back(NSTexture);
	surf = IMG_Load("sprites/Alphabet_02.png");
	SDL_Texture* ABTexture = SDL_CreateTextureFromSurface(r, surf);
	textures.push_back(ABTexture);
	surf = IMG_Load("sprites/nextBurron.png");
	SDL_Texture* NBTexture = SDL_CreateTextureFromSurface(r, surf);
	textures.push_back(NBTexture);
	//===
	SDL_FreeSurface(surf);
	//===================

	//init buttons
	for (int x = 0; x < 5; x++) {
		SDL_Rect* tempRect = new SDL_Rect;
		*tempRect = { 25+(92*x),492,55,55 };
		buttons.push_back(new Button(tempRect, x));
	}
	SDL_Rect* nextRect = new SDL_Rect;
	*nextRect = { 550,600,100,50 };
	buttons.push_back(new Button(nextRect, -1));

	questions.push_back( { "DO YOU FIND SOCIAL INTERACTION TIRING?",{ { 1,1,1 },{ 2,3,66 } } });
	questions.push_back({ "ARE YOU GOOD AT MATH?",{ {12,12,12}} });
}
void Game::cleanup() {
	for (int x = 0; x < textures.size(); x++) {
		SDL_DestroyTexture(textures[x]);
	}
}