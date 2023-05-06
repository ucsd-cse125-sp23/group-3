#include <ws2tcpip.h>
#include <stdio.h> 
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include "../shared/Packet.h"
#include <Constants.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

#define _WIN32_WINNT _WIN32_WINNT_WINXP // mingw bug
#define DEFAULT_ADDR "128.54.70.32"
#define DEFAULT_PORT "2400"

class Client
{
public:
	Client();
	void update();
	int accept_init();
	int recv_gamedata();
	void send_event(EventType e);
	void send_eventRecords(std::vector<int> records);

	void updateGameData(GameData);

	GameData* gd;

private:
	SOCKET ConnectSocket;
    char buffer[512];

};

