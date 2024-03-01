#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#include "SDL.h"
#include <utility>   //do i need this???, yes
#include <time.h>
#include "SDL_image.h"
#include <unordered_map> //do i need this?
#include <string>
#include <vector>
#include "filesystem"
#include <iostream>

#include "TextureManager.h"
#include "Game.h"




#define DEFAULT_PORT "41352"


int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("Needs an address");
		return 1;
	}


	//=========== SETUP THE SOCKET ========
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int iResult;
	char* pEnd;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}
	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n ");
		printf("%d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	

	//=========== SETUP THE SOCKET ========



	//====== SETUP THE VISUALS==========
	SDL_Init(SDL_INIT_VIDEO);//??
	SDL_Init(SDL_INIT_EVERYTHING);
	//atexit(SDL_Quit);
	srand(time(NULL));

	SDL_Window *MAINscreen = SDL_CreateWindow("Connect4",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //SDL_WINDOWPOS_UNDEFINED
		512, 512,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		NULL
	);
	SDL_Renderer *MAINrenderer = SDL_CreateRenderer(MAINscreen, -1, 0);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(MAINrenderer, 100, 100, 100, 255);
	SDL_RenderClear(MAINrenderer);
	SDL_RenderPresent(MAINrenderer);
	//====== SETUP THE VISUALS==========

	signed char tempColor = 0;
	bool tempTurn = false;

	//get inital game data from server
	iResult = recv(ConnectSocket, (char*)&tempColor, sizeof(tempColor), 0);
	iResult = recv(ConnectSocket, (char*)&tempTurn, sizeof(tempTurn), 0);

	//setups
	TextureManager::setup(MAINrenderer);
	Game::setup(MAINrenderer,tempColor,tempTurn,&ConnectSocket);

	


	//========= RUN THE GAME==============
	Game::run();
	//====================================



	//cleanups
	Game::cleanup();
	TextureManager::cleanup();

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		SDL_Quit();
		WSACleanup();
		return 1;
	}


	//close
	SDL_Quit();
	closesocket(ConnectSocket);
	WSACleanup();
	printf("Everything went swimmingly.");
	return 0;
}