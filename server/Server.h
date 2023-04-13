#include <winsock2.h>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP // mingw bug
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

#include <iostream>


const int NUM_PLAYERS = 4;

class Server
{
public:
	Server();
	~Server();
	int update();

	char buffer[NUM_PLAYERS][512];
	SOCKET ListenSocket;

	SOCKET sessions[NUM_PLAYERS];
};