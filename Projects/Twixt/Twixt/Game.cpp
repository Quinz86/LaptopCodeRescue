#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <stdlib.h>
#include "MyServerWrapper.cpp"
//#include "SegmentIntersection.h"   //this gives an error if its included???? even tho it already says pragma once???? whts going on ????

//statics
SDL_Point Game::mouseLocation = {0,0};
SDL_Renderer* Game::r = nullptr;

bool Game::done = false;
bool Game::myColor = true; //true = red, false = black
bool Game::myTurn = false;
bool Game::pegLink = true; //true = peg, false = link
bool Game::placedPeg = false;
bool Game::changesMade = false;
SDL_Point Game::selectedPeg = {-1,-1};
bool Game::selecting = false;

Board Game::realBoard = {};
Board Game::editBoard = {};

SDL_Rect Game::board_RECT = { 0, 0, 576, 576 };
SDL_Rect Game::menu_RECT = { 576, 0, 200, 576 };
SDL_Rect Game::pegB_RECT = { 594, 33, 77, 54 };
SDL_Rect Game::linkB_RECT = { 681, 33, 77, 54 };
SDL_Rect Game::finishmoveB_RECT = { 594, 97, 164, 54 };
SDL_Rect Game::resetB_RECT = { 594, 97+10+54, 164, 54 };
SDL_Rect Game::wating_RECT = { 594, 97+10+54+10+54, 164, 54 };
SDL_Rect Game::conB_RECT = { 594, 388, 164, 54 };
SDL_Rect Game::coning_RECT = { 594, 442, 164, 54 };
SDL_Rect Game::exitB_RECT = { 594, 496, 164, 54 };


int Game::connectingTimer = -1;
int Game::waitingTimer = -1;


MyServerWrapper<Message> Game::serv = {}; // something going on here? 
std::string Game::ip = "127.0.0.1";




void Game::setup(SDL_Renderer* rn, std::string internetprotocol) {
	r = rn;
	ip = internetprotocol;
}
void Game::run() {

	SDL_Texture* board_SPRT = TextureManager::myTextureGet("Board.png");

	SDL_Texture* BlackPeg_SPRT = TextureManager::myTextureGet("BlackPeg.png");
	SDL_Texture* RedPeg_SPRT = TextureManager::myTextureGet("RedPeg.png");
	SDL_Texture* BlackLink_SPRT = TextureManager::myTextureGet("BlackLink.png");
	SDL_Texture* RedLink_SPRT = TextureManager::myTextureGet("RedLink.png");

	SDL_Texture* SYIndic_SPRT = TextureManager::myTextureGet("SmallYellowIndicator.png");
	SDL_Texture* LYIndic_SPRT = TextureManager::myTextureGet("LargeYellowIndicator.png");
	SDL_Texture* LGIndic_SPRT = TextureManager::myTextureGet("LargeGreenIndicator.png");
	
	SDL_Texture* ALGB_SPRT = TextureManager::myTextureGet("Buttons/ActiveLargeGreenButton.png");
	SDL_Texture* ALYB_SPRT = TextureManager::myTextureGet("Buttons/ActiveLargeYellowButton.png");
	SDL_Texture* ALRB_SPRT = TextureManager::myTextureGet("Buttons/ActiveLargeRedButton.png");
	SDL_Texture* ASBB_SPRT = TextureManager::myTextureGet("Buttons/ActiveSmallBlackButton.png");
	SDL_Texture* ASRB_SPRT = TextureManager::myTextureGet("Buttons/ActiveSmallRedButton.png");
	SDL_Texture* DLGB_SPRT = TextureManager::myTextureGet("Buttons/DormantLargeGreenButton.png");
	SDL_Texture* DLYB_SPRT = TextureManager::myTextureGet("Buttons/DormantLargeYellowButton.png");
	SDL_Texture* DLRB_SPRT = TextureManager::myTextureGet("Buttons/DormantLargeRedButton.png");
	SDL_Texture* DSBB_SPRT = TextureManager::myTextureGet("Buttons/DormantSmallBlackButton.png");
	SDL_Texture* DSRB_SPRT = TextureManager::myTextureGet("Buttons/DormantSmallRedButton.png");
	SDL_Texture* ILB_SPRT = TextureManager::myTextureGet("Buttons/InactiveLargeButton.png");
	SDL_Texture* ISB_SPRT = TextureManager::myTextureGet("Buttons/InactiveSmallButton.png");

	SDL_Texture* con1_SPRT = TextureManager::myTextureGet("ConnectingAnimation/Connecting1.png");
	SDL_Texture* con2_SPRT = TextureManager::myTextureGet("ConnectingAnimation/Connecting2.png");
	SDL_Texture* con3_SPRT = TextureManager::myTextureGet("ConnectingAnimation/Connecting3.png");
	SDL_Texture* con4_SPRT = TextureManager::myTextureGet("ConnectingAnimation/Connecting4.png");
	SDL_Texture* cond_SPRT = TextureManager::myTextureGet("ConnectingAnimation/Connected.png");

	SDL_Texture* wat1_SPRT = TextureManager::myTextureGet("WaitingAnimation/Waiting1.png");
	SDL_Texture* wat2_SPRT = TextureManager::myTextureGet("WaitingAnimation/Waiting2.png");
	SDL_Texture* wat3_SPRT = TextureManager::myTextureGet("WaitingAnimation/Waiting3.png");
	SDL_Texture* wat4_SPRT = TextureManager::myTextureGet("WaitingAnimation/Waiting4.png");

	SDL_Texture* menuWords_SPRT = TextureManager::myTextureGet("SideBarMenuWords.png");

	SDL_Rect PegStamper = { 0,0,24,24 };
	SDL_Rect LinkStamper = { 0,0,72,48 };
	SDL_Point LinkRotator = {0,0};


	//=====<sandbox>==========
	/*

	int p = 10;
	int* q = &p;
	std::cout << sizeof(q) << std::endl;
	*/
	//======</sandbox>========




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
					case SDLK_SPACE: spaceBar(); break;
					//case SDLK_RETURN: myColor = !myColor; break; // testing only
					
					case SDLK_c: 
						serv.getMutex()->lock();
							std::cout << "Serv Status: " << serv.getStatus() << std::endl;
						serv.getMutex()->unlock();
						break;
					}
					
				}; break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) { // left click
					handleClick();
				} else if (event.button.button == SDL_BUTTON_RIGHT) { // right click

				}; break;
			case SDL_MOUSEMOTION:
				mouseLocation = { event.motion.x, event.motion.y };
				break;
			}

		}//end event handling


		//heres the interesting bits
		if (connectingTimer != -1) {
			if (serv.getMutex()->try_lock()) { //dont put anything else in this if(), because unlock() has to get called anyway
				//do stuff
				int s = serv.getStatus();
				serv.getMutex()->unlock();

				switch (s) {
				case 0: connectingTimer = -1;  break; //useful, dont get rid of
				case 1: break;
				case 2: if (connectingTimer >= 0) { connectingTimer = -2; } break; //
				case 3: 
					serv.getMutex()->lock();//not ideal, but whatever
					Message m = serv.checkInBox();
					serv.getMutex()->unlock();

					if ((m.ind & 0b10000000) > 0) { // shut down
						serv.closeDown();
						break;
					}
					if ((m.ind & 0b01000000) > 0) { // game end
						printf("Game ended\n");
						serv.closeDown();
						break;
					}
					if ((m.ind & 0b00100000) > 0) { // game start
						myColor = ((m.ind & 0b00010000) > 0); //color
					}
					if ((m.ind & 0b00001000) > 0) {

					}
					if ((m.ind & 0b00000100) > 0) { 
						
					}
					myTurn = ((m.ind & 0b00000010) > 0); // turn
					if ((m.ind & 0b00000001) > 0) { // new map
						realBoard = m.b;
						editBoard = realBoard;
					}
					break;
				case 4: serv.closeDown(); printf("Server shut down gracefully \n");  break;
				case 5: serv.closeDown(); printf("There was an error, closing down thread\n");  break;
				default: break; // this should never happen
				}
				
				
				
			}
		}
		if (waitingTimer >= 0 && myTurn) {
			waitingTimer = -1;
		} else if (waitingTimer == -1 && !myTurn) {
			waitingTimer = 0;
		}
		//end interesting bits


		
		//render
		//start blits
		SDL_RenderCopy(r, board_SPRT, NULL, &board_RECT);
		for (char x = 0; x < 24; x++) {
			for (char y = 0; y < 24; y++) {
				Peg tempPeg = editBoard.grid[x][y];
				if (tempPeg.active) {
					PegStamper.x = 24 * x;
					PegStamper.y = 24 * y;

					if (tempPeg.color) { //red
						SDL_RenderCopy(r, RedPeg_SPRT, NULL, &PegStamper);
						if (tempPeg.getConnection(0)) { LinkStamper.x = (x)*24; LinkStamper.y = (y+1)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 270, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(1)) { LinkStamper.x = (x)*24; LinkStamper.y = (y-1)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_NONE); }
						if (tempPeg.getConnection(2)) { LinkStamper.x = (x)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(3)) { LinkStamper.x = (x+2)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 90, &LinkRotator, SDL_FLIP_NONE); }
						if (tempPeg.getConnection(4)) { LinkStamper.x = (x+1)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 90, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(5)) { LinkStamper.x = (x-2)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_NONE); }
						if (tempPeg.getConnection(6)) { LinkStamper.x = (x-2)*24; LinkStamper.y = (y-1)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(7)) { LinkStamper.x = (x-1)*24; LinkStamper.y = (y+1)*24; SDL_RenderCopyEx(r, RedLink_SPRT, NULL, &LinkStamper, 270, &LinkRotator, SDL_FLIP_NONE); }
					} else { //black
						SDL_RenderCopy(r, BlackPeg_SPRT, NULL, &PegStamper);
						if (tempPeg.getConnection(0)) { LinkStamper.x = (x)*24; LinkStamper.y = (y+1)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 270, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(1)) { LinkStamper.x = (x)*24; LinkStamper.y = (y-1)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_NONE); }
						if (tempPeg.getConnection(2)) { LinkStamper.x = (x)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(3)) { LinkStamper.x = (x+2)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 90, &LinkRotator, SDL_FLIP_NONE); }
						if (tempPeg.getConnection(4)) { LinkStamper.x = (x+1)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 90, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(5)) { LinkStamper.x = (x-2)*24; LinkStamper.y = (y)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_NONE); }
						if (tempPeg.getConnection(6)) { LinkStamper.x = (x-2)*24; LinkStamper.y = (y-1)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 0, &LinkRotator, SDL_FLIP_VERTICAL); }
						if (tempPeg.getConnection(7)) { LinkStamper.x = (x-1)*24; LinkStamper.y = (y+1)*24; SDL_RenderCopyEx(r, BlackLink_SPRT, NULL, &LinkStamper, 270, &LinkRotator, SDL_FLIP_NONE); }
					}
				}
			}
		}

		if (myTurn) {
			//////=======================INDICATORS======================
			if (mouseLocation.x < 576) {
				char gdx = mouseLocation.x / 24;
				char gdy = mouseLocation.y / 24;
				if (!(myColor && (gdy == 0 || gdy == 23)) && !(!myColor && (gdx == 0 || gdx == 23))) {
					Peg& tempPeg = editBoard.grid[gdx][gdy];
					if (pegLink) { //peg
						if (!tempPeg.active) { // not active -- small
							if (!placedPeg) {
								PegStamper.x = gdx * 24; PegStamper.y = gdy * 24;
								SDL_RenderCopy(r, SYIndic_SPRT, NULL, &PegStamper);
							}
						} else { // active -- large
							if (tempPeg.color == myColor) {
								PegStamper.x = gdx * 24; PegStamper.y = gdy * 24;
								SDL_RenderCopy(r, LYIndic_SPRT, NULL, &PegStamper);
							}
						}
					} else { //link
						if (selecting) {
							PegStamper.x = selectedPeg.x * 24; PegStamper.y = selectedPeg.y * 24;
							SDL_RenderCopy(r, LGIndic_SPRT, NULL, &PegStamper);
						}
						if (tempPeg.color == myColor && tempPeg.active) {
							PegStamper.x = gdx * 24; PegStamper.y = gdy * 24;
							SDL_RenderCopy(r, LYIndic_SPRT, NULL, &PegStamper);
						}
					}
				}
			}
			//////=======================INDICATORS======================
			if (myColor) { //red
				if (pegLink) { // peg
					SDL_RenderCopy(r, DSRB_SPRT, NULL, &pegB_RECT);
					SDL_RenderCopy(r, ASRB_SPRT, NULL, &linkB_RECT);
				} else { //link
					SDL_RenderCopy(r, ASRB_SPRT, NULL, &pegB_RECT);
					SDL_RenderCopy(r, DSRB_SPRT, NULL, &linkB_RECT);
				}
			} else { //black
				if (pegLink) { // peg
					SDL_RenderCopy(r, DSBB_SPRT, NULL, &pegB_RECT);
					SDL_RenderCopy(r, ASBB_SPRT, NULL, &linkB_RECT);
				} else { //link
					SDL_RenderCopy(r, ASBB_SPRT, NULL, &pegB_RECT);
					SDL_RenderCopy(r, DSBB_SPRT, NULL, &linkB_RECT);
				}
			}
			///======================\Indicators===============
			if (placedPeg) { //activate finish move button
				SDL_RenderCopy(r, ALGB_SPRT, NULL, &finishmoveB_RECT);
			} else {
				SDL_RenderCopy(r, DLGB_SPRT, NULL, &finishmoveB_RECT);
			}
			if (changesMade) { //activate reset button
				SDL_RenderCopy(r, ALYB_SPRT, NULL, &resetB_RECT);
			} else {
				SDL_RenderCopy(r, DLYB_SPRT, NULL, &resetB_RECT);
			}
		}else{
			SDL_RenderCopy(r, ISB_SPRT, NULL, &pegB_RECT);
			SDL_RenderCopy(r, ISB_SPRT, NULL, &linkB_RECT);
			SDL_RenderCopy(r, ILB_SPRT, NULL, &finishmoveB_RECT);
			SDL_RenderCopy(r, ILB_SPRT, NULL, &resetB_RECT);
		}
		if (connectingTimer == -1) {//connect button
			SDL_RenderCopy(r, ALGB_SPRT, NULL, &conB_RECT);
		} else {
			SDL_RenderCopy(r, ILB_SPRT, NULL, &conB_RECT);
		}
		if (connectingTimer >= 0) { //connecting animation
			connectingTimer++;
			if (connectingTimer >= 400) {
				connectingTimer = 0;
			}
			if (connectingTimer < 100) {
				SDL_RenderCopy(r, con1_SPRT, NULL, &coning_RECT);
			} else if (connectingTimer < 200) {
				SDL_RenderCopy(r, con2_SPRT, NULL, &coning_RECT);
			} else if (connectingTimer < 300) {
				SDL_RenderCopy(r, con3_SPRT, NULL, &coning_RECT);
			} else if (connectingTimer < 400) {
				SDL_RenderCopy(r, con4_SPRT, NULL, &coning_RECT);
			}
		} else if (connectingTimer == -2) {
			SDL_RenderCopy(r, cond_SPRT, NULL, &coning_RECT);
		}
		if (waitingTimer >= 0) { //waiting animation
			waitingTimer++;
			if (waitingTimer >= 400) {
				waitingTimer = 0;
			}
			if (waitingTimer < 100) {
				SDL_RenderCopy(r, wat1_SPRT, NULL, &wating_RECT);
			} else if (waitingTimer < 200) {
				SDL_RenderCopy(r, wat2_SPRT, NULL, &wating_RECT);
			} else if (waitingTimer < 300) {
				SDL_RenderCopy(r, wat3_SPRT, NULL, &wating_RECT);
			} else if (waitingTimer < 400) {
				SDL_RenderCopy(r, wat4_SPRT, NULL, &wating_RECT);
			}
		}
		SDL_RenderCopy(r, ALRB_SPRT, NULL, &exitB_RECT);
		SDL_RenderCopy(r, menuWords_SPRT, NULL, &menu_RECT);
		//finish blitting

		SDL_RenderPresent(r);
		SDL_RenderClear(r);
	}
	//end game loop (done == true)
}
void Game::cleanup() {
	//DONT call lock() here
	serv.closeDown(); // should be safe to call even if not connected (status == 0 or 5) 
}






void Game::handleClick() {
	if (myTurn) {
		if (mouseLocation.x < 576) {
			char gdx = mouseLocation.x / 24;
			char gdy = mouseLocation.y / 24;
			
			if ((myColor && (gdy == 0 || gdy == 23)) || (!myColor && (gdx == 0 || gdx == 23))) {
				return;
			}

			Peg& tempPeg = editBoard.grid[gdx][gdy];
			if ( !tempPeg.active ){  
				if (pegLink && !placedPeg) {  //peg
					editBoard.addPeg({ gdx,gdy }, myColor);
					changesMade = true;
					placedPeg = true;
					pegLink = false;  //if you want to automate the switch
				}
			} else if(tempPeg.color == myColor) {
				if (pegLink) {
					editBoard.removePeg({ gdx,gdy });
					changesMade = true;
				} else {
					if (selecting) {
						if(gdx == selectedPeg.x && gdy == selectedPeg.y){
							selecting = false;
							//dont need to reset selectedPeg because selecting is false
						} else if( editBoard.flipConnection(selectedPeg, {gdx,gdy}) ){
							changesMade = true;
							selecting = false;
							//dont need to reset selectedPeg because selecting is false
						}
					} else {
						selectedPeg = { gdx, gdy };
						selecting = true;
					}
				}
			}
		} else {//in game menu buttons
			if (SDL_PointInRect(&mouseLocation, &pegB_RECT)) {
				pegLink = true;
				selecting = false;
			} else if (SDL_PointInRect(&mouseLocation, &linkB_RECT)){
				pegLink = false;
			} else if (SDL_PointInRect(&mouseLocation, &finishmoveB_RECT)) {
				if (placedPeg) {
					spaceBar();
					
				}
			} else if (SDL_PointInRect(&mouseLocation, &resetB_RECT)) {
				resetEdit();
			}
		}
		
	}
	//menu buttons here that dont depend on it being yur turn
	if (connectingTimer == -1 && SDL_PointInRect(&mouseLocation, &conB_RECT)) {
		//start connecting
		bool goAhead = true;
		serv.getMutex()->lock();
			if (serv.getStatus() != 0 ) { goAhead = false; } //this is a fail safe, idk how it would happen
		serv.getMutex()->unlock();

		if (goAhead) {
			connectingTimer = 0;
			serv.startUp(ip, DEFAULT_PORT);
		}
	}
	if (SDL_PointInRect(&mouseLocation, &exitB_RECT)) {
		serv.setOutBox({realBoard,0b01000001});
		done = true;
	}
}

void Game::resetEdit() {
	editBoard = realBoard;
	changesMade = false;
	placedPeg = false;
	selecting = false;
	pegLink = true; // for convenience
}

//===================================================================================================================

void Game::spaceBar() {
	changesMade = false;
	myTurn = false;
	placedPeg = false;
	selecting = false;
	realBoard = editBoard;
	pegLink = true; // for convinience 
	//myColor = !myColor;
	Message m = {};
	m.b = realBoard;
	m.ind = 0b00000001;
	serv.setOutBox(m);
}
