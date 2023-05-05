#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "../../shared/Packet.h"
#include "CollisionDetection.h"
#include "core.h"

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>
#include <unordered_map>

#pragma comment (lib, "Ws2_32.lib")

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WINXP // mingw bug
#define DEFAULT_PORT "2400"

const int NUM_PLAYERS = 4;

class Server
{
public:
	Server();
	~Server();
	int update();
	void send_init_packet(int client_id, int character_id);
	void send_gamedata(int client_id);
	int recv_event(int client_id);
	std::vector<int> recv_eventRecords(int client_id);
	bool check_attackability(int player_id, int obs_id);

	char buffer[NUM_PLAYERS][512];
	SOCKET ListenSocket;

	SOCKET sessions[NUM_PLAYERS];

	GameData* gd;
	Event e[NUM_PLAYERS];

	static Map* map;
	static CollisionDetection collisionDetection;
	
	void updateByEvent(std::unordered_map<int, std::vector<int>> events);
	void updateBySingleEvent(EventType e, int character);

	void updateInsecurity(int increase);
	void check_A_Distance();

	std::vector<int> ids{ 0,1,2,3 };
	std::vector<int> check_event{ -1, -1, -1, -1 };

	std::vector<std::pair<int, int>> obs_countdown;
};