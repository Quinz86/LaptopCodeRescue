#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#include "Move.h"


#define DEFAULT_PORT "41352"

int __cdecl main(void)
{
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

	printf("Now listening for clients");
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

	//send initial game data
	signed char tempColor = 1;
	bool tempTurn = true;
	iSendResult = send(ClientSocket1, (char*)&tempColor, sizeof(tempColor), 0);
	iSendResult = send(ClientSocket1, (char*)&tempTurn, sizeof(tempTurn), 0);
	tempColor = -1;
	tempTurn = false;
	iSendResult = send(ClientSocket2, (char*)&tempColor, sizeof(tempColor), 0);
	iSendResult = send(ClientSocket2, (char*)&tempTurn, sizeof(tempTurn), 0);

	signed char grid[7][6] = { { 0,0,0,0,0,0 },
							   { 0,0,0,0,0,0 },
							   { 0,0,0,0,0,0 },
							   { 0,0,0,0,0,0 },
							   { 0,0,0,0,0,0 },
							   { 0,0,0,0,0,0 },
							   { 0,0,0,0,0,0 } };


	printf("Game Start!\n)");

	bool done = false;
	Move m;
	do {
		iResult = recv(ClientSocket1, (char*)&m, sizeof(m), 0);
		if (iResult <= 0) {done = true;break;}
		grid[m.x][m.y] = m.color;
		iResult = send(ClientSocket2, (char*)&m, sizeof(m), 0);
		if (iResult <= 0) { done = true; break; }


		iResult = recv(ClientSocket2, (char*)&m, sizeof(m), 0);
		if (iResult <= 0) { done = true; break; }
		grid[m.x][m.y] = m.color;
		iResult = send(ClientSocket1, (char*)&m, sizeof(m), 0);
		if (iResult <= 0) { done = true; break; }
		
	} while (!done);// iResult > 0);

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