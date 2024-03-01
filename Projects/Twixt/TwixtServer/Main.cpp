

#include <iostream>



#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")






#include "MessageCopy.h"
#include "BoardCopy.h"

#define DEFAULT_PORT "41352"

int main(int argc, char ** argv) {
	std::cout << "Please" << std::endl;

	//========set up the socket========
	WSADATA wsaData;
	int iResult;
	int iSendResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket1 = INVALID_SOCKET;
	SOCKET ClientSocket2 = INVALID_SOCKET;


	struct addrinfo *result = NULL;
	struct addrinfo hints;




	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf("Now listening for clients\n");
	// Accept a client socket
	ClientSocket1 = accept(ListenSocket, NULL, NULL);
	if (ClientSocket1 == INVALID_SOCKET) {
		printf("accept 1 failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Client 1 Connected.\n");
	ClientSocket2 = accept(ListenSocket, NULL, NULL);
	if (ClientSocket2 == INVALID_SOCKET) {
		printf("accept 2 failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Client 2 Connected.\n");

	// No longer need server socket
	closesocket(ListenSocket);


	//===============================================================================
	//DO STUFF HERE
	SOCKET players[2] = { ClientSocket1, ClientSocket2 };


	//send initial game data
	Board trueBoard = {};
	Message m = {};
	m.b = trueBoard;

	m.ind = 0b00110001;
	iSendResult = send(ClientSocket1, (char*)&m, sizeof(m), 0); //Red
	m.ind = 0b00100001;
	iSendResult = send(ClientSocket2, (char*)&m, sizeof(m), 0); //Black


	printf("Game Start!\n");

	m.ind = 0b00000011;

	int numTurns = 0;
	bool gameover = false;
	bool fail = false;
	do {
				printf("Player: %d's Turn\n", (numTurns % 2));
		m.ind = 0b00000011;
		iResult = send(players[numTurns % 2], (char*)&m, sizeof(m), 0);
		if (iResult <= 0) { fail = true; break; }
				printf("Sent successfully, waiting for response from player %d\n", (numTurns % 2));
		iResult = recv(players[numTurns % 2], (char*)&m, sizeof(m), 0);
		if (iResult <= 0) { fail = true; break; }
		if ((m.ind & 0b00000001) > 0) {
			trueBoard = m.b;
		}
		if ((m.ind & 0b01000000) > 0) {
			gameover = true;
		}
		numTurns++;

	} while (!gameover && !fail);// iResult > 0);
	if (fail) {
		printf("Fail\n");
	}
	if (gameover) {
		printf("Gameover\n");
		m.ind = 0b01000001;
		iResult = send(players[numTurns % 2], (char*)&m, sizeof(m), 0);
	}
	//===============================================================================
	


	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket1, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown 1 failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket1);
		WSACleanup();
		return 1;
	}
	iResult = shutdown(ClientSocket2, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown 2 failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket2);
		WSACleanup();
		return 1;
	}
	// cleanup
	closesocket(ClientSocket1);
	closesocket(ClientSocket2);
	WSACleanup();

	return 0;
}