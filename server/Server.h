#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "../shared/Packet.h"

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#pragma comment (lib, "Ws2_32.lib")

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WINXP // mingw bug
#define DEFAULT_PORT "2400"

const int NUM_PLAYERS = 1;

class Server
{
public:
	Server();
	~Server();
	int update();
	void send_init_packet(int client_id, int character_id);
	void send_gamedata(int client_id);
	int recv_event(int client_id);

	char buffer[NUM_PLAYERS][512];
	SOCKET ListenSocket;

	SOCKET sessions[NUM_PLAYERS];

	GameData* gd;
	Event e[NUM_PLAYERS];
	
	void updateByEvent(EventType, EventType, EventType, EventType);
	void updateBySingleEvent(EventType, int);

	std::vector<int> ids{ 0,1,2,3 };
};