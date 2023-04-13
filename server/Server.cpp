#include "Server.h"

Server::Server()
{
	WSADATA wsaData;
	int iResult;

	ListenSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(1);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP; 
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if ( iResult != 0 ) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		exit(1);
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}
	u_long argp = 1;
	iResult = ioctlsocket(ListenSocket, FIONBIO, &argp);
	if (iResult == SOCKET_ERROR) {
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	// Setup the TCP listening socket
	iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	freeaddrinfo(result);

	// start listening for new clients attempting to connect
	iResult = listen(ListenSocket, SOMAXCONN);

	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
}
Server::~Server(){
	closesocket(ListenSocket);
	WSACleanup();
}
int Server::update()
{

	for (int id = 0; id < NUM_PLAYERS; id ++){
		if (sessions[id] != INVALID_SOCKET && recv(sessions[id], buffer[id], 512, 0) > 0)
		{
			printf("%s\n", buffer[id]);

			if(buffer[id][0] == 'q'){
				closesocket(sessions[id]);
				sessions[id] = INVALID_SOCKET;
			}
			else{
				char echo[512] = "echo ";
				memcpy(&echo[strlen(echo)], buffer[id], strlen(buffer[id]));

				if (send(sessions[id], echo, 512, 0) == SOCKET_ERROR) 
				{
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(sessions[id]);
				}
			}
		}
	}
	bool valid = false;
	for (int id = 0; id < NUM_PLAYERS; id ++)
		valid = valid || sessions[id] != INVALID_SOCKET;

	if (!valid)
		return -1;

	return 0;
}