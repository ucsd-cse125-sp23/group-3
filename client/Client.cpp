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

	this->gd = new GameData();

	send(ConnectSocket, "start", 512, 0);
}

void Client::update()
{
	if (recv(ConnectSocket, buffer, 512, 0) <= 0) 
		return;
	GameData gd = Packet::deserializeGameData(buffer);
	this->updateGameData(gd);

	// printf("%s\n", buffer);
	std::cout << this->gd->gamestate_to_string() << std::endl;
	
	char input[512];
	std::cin >> input;
	send(ConnectSocket, input, 512, 0);
}

int Client::accept_init()
{
	if (recv(ConnectSocket, buffer, 512, 0) <= 0)
		return -1;

	switch (buffer[0])
	{
		case '0':
			std::cout << "character:" << "Alice" << std::endl;
			return 0;
		case '1':
			std::cout << "character:" << "Bob" << std::endl;
			return 1;
		case '2':
			std::cout << "character:" << "Carol" << std::endl;
			return 2;
		case '3':
			std::cout << "character:" << "Dave" << std::endl;
			return 3;
		default:
			break;
	}
	return -1;
}

int Client::recv_gamedata()
{
	if (recv(ConnectSocket, buffer, 512, 0) <= 0)
		return -1;
	GameData new_gd = Packet::deserializeGameData(buffer);
	this->updateGameData(new_gd);
	return 0;
}

void Client::send_event(EventType e)
{
	Event* event = new Event(e);
	Packet::serialize(event, buffer);
	send(ConnectSocket, buffer, 512, 0);
}

void Client::updateGameData(GameData gd) {
	this->gd->location_A = gd.location_A;
	this->gd->location_B = gd.location_B;
	this->gd->location_C = gd.location_C;
	this->gd->location_D = gd.location_D;

	this->gd->obstacle_states = gd.obstacle_states;

	this->gd->level_A = gd.level_A;
	this->gd->level_B = gd.level_B;
	this->gd->level_C = gd.level_C;
	this->gd->level_D = gd.level_D;

	this->gd->remaining_time = gd.remaining_time;

	this->gd->gamestate = gd.gamestate;
}

