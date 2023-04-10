#include <winsock2.h>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP // mingw bug
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

class Server
{
public:
	Server();
	void update();

private:
	char buffer[512];
	SOCKET ListenSocket;
	SOCKET session;
};