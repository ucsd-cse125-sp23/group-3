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

	for (int i = 0; i < NUM_PLAYERS; i++) {
		e[i] = Event(EventType::NOEVENT);
	}
	this->gd = new GameData();
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

void Server::send_init_packet(int character_id){
	if (sessions[character_id] != INVALID_SOCKET)
	{
		std::string init_str;
		// Init packet
		// init_str.append("0");
		init_str.append(std::to_string(character_id));
		const char* buf_init = init_str.c_str();
		std::cout << "sending init..." << buf_init << std::endl;
		if (send(sessions[character_id], buf_init, 2, 0) == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(sessions[character_id]);
		}
	}
	
}

void Server::send_gamedata(int client_id)
{
	if (sessions[client_id] != INVALID_SOCKET)
	{
		Packet::serialize(this->gd, buffer[client_id]);
		if (send(sessions[client_id], buffer[client_id], 512, 0) == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(sessions[client_id]);
		}
	}
}

int Server::recv_event(int client_id)
{
	if (recv(sessions[client_id], buffer[client_id], 512, 0) > 0)
	{
		Event event = Packet::deserializeEvent(buffer[client_id]);
		return (int)event.getEventType();
	}
	return -1;
}

void Server::updateBySingleEvent(EventType e, int id) {
	if (e == EventType::NOEVENT || (int)e == -1)
		return;
	glm::mat4* loc = NULL;
	switch (id)
	{
	case 0:
		loc = &this->gd->location_A;
		break;
	case 1:
		loc = &this->gd->location_B;
		break;
	case 2:
		loc = &this->gd->location_C;
		break;
	case 3:
		loc = &this->gd->location_D;
		break;
	default:
		break;
	}

	if (e == EventType::FORWARD) {
		*loc = glm::translate(*loc, glm::vec3(0, 0, -CAMERA_SPEED));
	}
	else if (e == EventType::TURN_LEFT) {
		*loc = *loc * glm::rotate(glm::radians(CAMERA_SPEED * TURNING_RATIO), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (e == EventType::TURN_RIGHT) {
		*loc = *loc * glm::rotate(glm::radians(-CAMERA_SPEED * TURNING_RATIO), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (e == EventType::ATTACK) {
		// Attack!!!
	}

}

void Server::updateByEvent(EventType e0, EventType e1, EventType e2, EventType e3) {
	if (this->gd->remaining_time >= 0) {
		this->gd->remaining_time -= TICK_TIME;
	}
	updateBySingleEvent(e0, 0);
	updateBySingleEvent(e1, 1);
	updateBySingleEvent(e2, 2);
	updateBySingleEvent(e3, 3);
}