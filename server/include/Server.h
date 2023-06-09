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


#include <chrono>

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
	bool check_detectability(int obs_id);

	char buffer[NUM_PLAYERS][512];
	SOCKET ListenSocket;

	SOCKET sessions[NUM_PLAYERS];

	GameData* gd;

	static Map* map;
	static CollisionDetection collisionDetection;
	
	void updateByEvent(std::unordered_map<int, std::vector<int>> events);
	void updateBySingleEvent(EventType e, int character);

	void updateInsecurity(int increase);
	void check_A_Distance();
	void handleAttack(int character_id);
	void handleDetect();
	void updateObstacleCountdown();
	void checkGameEndLogic();

	void broadcast_button_assignment();
	int handle_acq(int client);

	void handleBCDskill(int id);
	void updateSkillCD();
	// This function guarantees that each client will only receive one gamedata 
	// containing status == skill for one usage of skill to avoid double action
	void cleanUpSkillWalkStatus();
	void initialize_game();

	// index by player_id: 0 -> Alice
	std::vector<int> button_assignment{ -1, -1, -1, -1 };

	std::vector<int> ids{ -1,-1,-1,-1 };
	std::vector<int> check_event{ -1, -1, -1, -1 };

	// index by player_id: 0 -> Alice etc.; each pair represents obstacle_id - countdown time
	std::vector<std::pair<int, int>> obs_countdown;
	std::chrono::milliseconds prev = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);;
};