#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_ 

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <thread>
#include <mutex>

#include <string>

#include "Message.h"


//#define DEFAULT_PORT "41352"


template <typename T> //or <class T>
class MyServerWrapper {
public:
	MyServerWrapper();
	~MyServerWrapper();

	void startUp(std::string ADDRESS, std::string PORT);
	void closeDown();
	int getStatus();

	std::mutex* getMutex();
	T checkInBox();
	void setOutBox(T mes);

private:
	int status = 0;

	std::thread serverHandler;
	SOCKET connectionSocket = INVALID_SOCKET;
	std::mutex mtx;
	bool shouldClose = false;
	T inBox;

	int myConnect(std::string addr, std::string prt);
	void threadded();

	std::string ADDRESS;
	std::string PORT;
		
};


