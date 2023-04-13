#include "Client.h"

#include <iostream>
Client::Client()
{
	WSADATA wsaData;
	ConnectSocket = INVALID_SOCKET;

	// holds address info for socket to connect to
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(1);
	}
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	iResult = getaddrinfo(DEFAULT_ADDR, DEFAULT_PORT, &hints, &result);

	if( iResult != 0 ) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		exit(1);
	}

	// Attempt to connect to an address until one succeeds
	for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
			ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}

		// Connect to server.
		iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf ("The server is down... did not connect");
		}
	}

	freeaddrinfo(result);

	// if connection failed
	if (ConnectSocket == INVALID_SOCKET) 
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		exit(1);
	}

	u_long argp = 1;
	iResult = ioctlsocket(ConnectSocket, FIONBIO, &argp);
	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);        
	}

	send(ConnectSocket, "start", 512, 0);
}

void Client::update()
{
	if (recv(ConnectSocket, buffer, 512, 0) <= 0) 
		return;

	printf("%s\n", buffer);
	
	char input[512];
	std::cin >> input;
	send(ConnectSocket, input, 512, 0);
}

