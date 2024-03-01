#include "MyServerWrapper.h"
#include "Message.h"



template <typename T>
MyServerWrapper<T>::MyServerWrapper() {

}
template <typename T>
MyServerWrapper<T>::~MyServerWrapper() {
	
}






//mtx
template <typename T>
int MyServerWrapper<T>::getStatus() {
	//0 dormant, hasnt even connected
	//1 connecting ->2
	//2 connected
	//3 youve got mail 
	//4 shut down, needs join/detatch
	//5 error, needs join/detatch
	return status;
}
//\mtx

template <typename T>
std::mutex* MyServerWrapper<T>::getMutex() {
	return &mtx;
}
//remember to lock before calling this function
template <typename T>
T MyServerWrapper<T>::checkInBox() {
	status = 2;
	return inBox;
}
//remember to unlock after calling that function
template <typename T>
void MyServerWrapper<T>::setOutBox(T mes) {
	int i = send(connectionSocket, (char*)&mes, sizeof(mes), 0);
}


template <typename T>
void MyServerWrapper<T>::startUp(std::string addr, std::string prt) {
	mtx.lock();//might block, if ur dumb
		if ( status != 0 || serverHandler.joinable()) {
			printf("U shouldnt see this message; u tried to startUp() twice\n");
			std::cout << "status is: " << status << std::endl;
			mtx.unlock();
			return;
		}
		status = 1;
		shouldClose = false;
	mtx.unlock();

	ADDRESS = addr;
	PORT = prt;
	printf("about to start new Thread\n");
	serverHandler = std::thread(&MyServerWrapper::threadded, this);
}
template <typename T>
void MyServerWrapper<T>::closeDown() { //essentially a reset
	mtx.lock(); //should be regular lock bc we want to wait, cant lock outside of function bc threadded().join() needs the mutex
	shouldClose = true;
	mtx.unlock();
	if (serverHandler.joinable()) { //safety, not always be joinable, because double closeDown(), or close on application start
		serverHandler.join();
	}
	mtx.lock();
	status = 0;
	mtx.unlock();
	//WSACleanup(); // handled at the end of threaded()
}


template <typename T>
int MyServerWrapper<T>::myConnect(std::string addr, std::string prt) {
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

	iResult = getaddrinfo(addr.c_str(), prt.c_str(), &hints, &result);
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
		printf("Unable to connect to server!!!!!!!!\n ");
		printf("%d\n", WSAGetLastError());
		printf("before WSA clean up\n");
		WSACleanup();
		printf("after WSA clean up\n");
		return 1;
	}
	//=========== \SETUP THE SOCKET ========
	
	connectionSocket = ConnectSocket;
	return 0;
}

template <typename T>
void MyServerWrapper<T>::threadded() {
	bool stopThread = false; // needs to be separate because of multithreading and mutex

	int i = myConnect(ADDRESS, PORT); //concieveably could be other than 0 and 1
	printf("myConnect() returned with value %d\n", i);

	mtx.lock();
	switch (i) {
	case 0:	 status = 2; break;   
	default: printf("theres problems\n");/*theres problems*/ status = 5; stopThread = true;  break;
	}
	mtx.unlock();
	if (stopThread) {
		closesocket(connectionSocket);
		WSACleanup();
		printf("im about to return because of connect fail\n");
		return;
	}


	//==========================================================

	
	T mail;
	while (!stopThread) {
		int i = recv(connectionSocket, (char*)&mail, sizeof(mail), 0);
		mtx.lock(); //SHOULD be regular lock, bc the mail never fails,
		status = 3;
		inBox = mail;
		printf("Youve got mail!");

		if (i <= 0) { shouldClose = true; }
		if (shouldClose) {
			stopThread = true;
			status = 4;
		}
		if (i < 0) { status = 5; }
		mtx.unlock(); // should close is still in the mutex
		
	}
	closesocket(connectionSocket);
	WSACleanup();

}

