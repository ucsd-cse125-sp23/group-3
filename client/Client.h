#include <winsock2.h>
#include <Windows.h>

#define _WIN32_WINNT _WIN32_WINNT_WINXP // mingw bug

#include <ws2tcpip.h>
#include <stdio.h> 

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

class Client
{
public:
	Client();
	void update();

private:
	SOCKET ConnectSocket;
    char buffer[512];
};

