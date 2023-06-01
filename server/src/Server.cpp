#include "../include/Server.h"
#include <algorithm>
#include <chrono>

Map* Server::map;
CollisionDetection Server::collisionDetection;

Server::Server()
{
	//std::random_device rd;
	//std::mt19937 g(rd());
	//std::shuffle(ids.begin(), ids.end(), g);

	//for (auto a : ids)
	//	std::cout << a << " ";

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

void Server::send_init_packet(int client_id, int character_id){
	if (sessions[client_id] != INVALID_SOCKET)
	{
		std::string init_str;
		// Init packet
		// init_str.append("0");
		init_str.append(std::to_string(character_id));
		const char* buf_init = init_str.c_str();
		std::cout << "sending init..." << buf_init << std::endl;
		if (send(sessions[client_id], buf_init, 2, 0) == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(sessions[client_id]);
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

std::vector<int> Server::recv_eventRecords(int client_id)
{
	std::vector<int> eventRecord;
	if (recv(sessions[client_id], buffer[client_id], 512, 0) > 0)
	{
		eventRecord = Packet::deserializeEventRecords(buffer[client_id]);
		this->check_event[client_id] = 1;
	}
	return eventRecord;
}

bool Server::check_attackability(int player_id, int obs_id)
{
	glm::mat4* loc = NULL;
	switch (player_id)
	{
	case 0:
		return false; // Alice could not attack
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
	glm::vec4 transf(0, 0, -ATTACK_RANGE, 1);
	glm::vec4 ahead_point = *loc*transf;
	glm::vec2 player_pt(ahead_point[0], ahead_point[2]);
	float* pSourceObs = (float*)glm::value_ptr(map->obs->glm_vec[obs_id]);
	glm::vec2 centerObs(pSourceObs[12], pSourceObs[14]);
	return glm::length(player_pt-centerObs) < ATTACK_RANGE;
}

bool Server::check_detectability(int obs_id)
{
	glm::mat4* loc = &this->gd->location_A;
	glm::vec4 transf(0, 0, -2*ATTACK_RANGE, 1);
	glm::vec4 ahead_point = *loc * transf;
	glm::vec2 player_pt(ahead_point[0], ahead_point[2]);
	float* pSourceObs = (float*)glm::value_ptr(map->obs->glm_vec[obs_id]);
	glm::vec2 centerObs(pSourceObs[12], pSourceObs[14]);
	return glm::length(player_pt - centerObs) < 2*ATTACK_RANGE;
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
		glm::mat4 old_loc = *loc;
		*loc = glm::translate(*loc, glm::vec3(0, 0, -CAMERA_SPEED));
		int mapID;
		float x;
		float y;
		map->getPosition(*loc, &mapID, &y, &x);
		std::vector<std::pair<float, float>> points = map->getGrid(mapID, x, y);
		if ((collisionDetection.checkCollisionWithWall(mapID, points))) {
			*loc = old_loc;
		}
		int obs_type;
		if (collisionDetection.collideWithObstacle(*loc, map->obs->obs_vec, &obs_type)) { // collide with obstacle
			*loc = old_loc;
			if (id == 0)
			{
				int increase = 0;
				switch (obs_type)
				{
				case 1:
					increase = SMALL_ALERT;
				case 2:
					increase = MEDIUM_ALERT;
				case 3:
					increase = LARGE_ALERT;
				default:
					break;
				}
				updateInsecurity(increase);
			}
		}
	}
	else if (e == EventType::TURN_LEFT) {
		*loc = *loc * glm::rotate(glm::radians(CAMERA_SPEED * TURNING_RATIO), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (e == EventType::TURN_RIGHT) {
		*loc = *loc * glm::rotate(glm::radians(-CAMERA_SPEED * TURNING_RATIO), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (e == EventType::ATTACK) {
		if (id != 0)
		{
			handleAttack(id);
		}
	}
	else if (e == EventType::SKILL)
	{
		if (id == 0) {
			// handle Alice's skill
			handleDetect();
		}
		else {
			handleBCDskill(id);
		}
	}
}

void Server::handleAttack(int id)
{
	for (int i = 0; i < map->obs->glm_vec.size(); i++)
	{
		bool attack_success = check_attackability(id, i);
		if (attack_success && this->gd->obstacle_states[i] == (int)ObstacleState::NOT_DESTROYED)
		{
			std::cout << i << "is being attacked by " << id <<"!!!" << std::endl;
			int obs_type = map->obs->obs_vec[i]->type;
			int cd_time = 0;
			switch (obs_type)
			{
			case 1:
				cd_time = SMALL_OBS;
				break;
			case 2:
				cd_time = MEDIUM_OBS;
				break;
			case 3:
				cd_time = LARGE_OBS;
				break;
			default:
				break;
			}
			std::pair<int, int> obs_data = std::make_pair(i, cd_time);
			this->obs_countdown[id] = obs_data;
			this->gd->obstacle_states[i] = (int)ObstacleState::CURRENTLY_DESTROYING;
			this->gd->player_status[id] = (int)PlayerStatus::ATTACK;
		}
	}
}

void Server::handleDetect()
{
	if (this->gd->skill_cd[0] > 0)
	{
		return;
	}

	// TODO: Alice skill cd
	this->gd->skill_cd[0] = SKILL_CD;
	this->gd->player_status[0] = (int)PlayerStatus::SKILL;

	for (int i = 0; i < map->obs->glm_vec.size(); i++)
	{
		bool detect_success = check_detectability(i);
		if (detect_success && this->gd->obstacle_states[i] == (int)ObstacleState::NOT_DESTROYED)
		{
			std::cout << i << "is being detected" << "!!!" << std::endl;
			/*int obs_type = map->obs->obs_vec[i]->type;
			std::pair<int, int> obs_data = std::make_pair(i, 2000);
			this->obs_countdown[0] = obs_data;*/
			this->gd->obstacle_states[i] = (int)ObstacleState::DETECTED;
		}
	}
}

void Server::updateObstacleCountdown()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (this->obs_countdown[i].first != -1) {
			this->obs_countdown[i].second -= TICK_TIME;
			if (this->obs_countdown[i].second <= 0)
			{
				// update level of awareness
				int obs_type = map->obs->obs_vec[this->obs_countdown[i].first]->type;
				int award = 0;
				switch (obs_type)
				{
				case 1:
					award = SMALL_AWD;
					break;
				case 2:
					award = MEDIUM_AWD;
					break;
				case 3:
					award = LARGE_AWD;
					break;
				default:
					break;
				}
				int sum = 0;
				switch (i)
				{
				case 1:
					sum = this->gd->level_B + award;
					this->gd->level_B = sum >= MAX_AWARENESS ? MAX_AWARENESS : sum;
					//this->gd->level_B += award;
					break;
				case 2:
					sum = this->gd->level_C + award;
					this->gd->level_C = sum >= MAX_AWARENESS ? MAX_AWARENESS : sum;
					//this->gd->level_C += award;
					break;
				case 3:
					sum = this->gd->level_D + award;
					this->gd->level_D = sum >= MAX_AWARENESS ? MAX_AWARENESS : sum;
					//this->gd->level_D += award;
					break;
				default:
					break;
				}
				if (i != 0) { // BCD attack
					this->map->obs->obs_vec[this->obs_countdown[i].first] = nullptr;
					this->gd->obstacle_states[this->obs_countdown[i].first] = (int)ObstacleState::DESTROYED;
				}
				this->gd->player_status[i] = (int)PlayerStatus::NONE;
				this->obs_countdown[i] = std::make_pair(-1, -1);
			}
		}
	}

	for (int i = 0; i < gd->obstacle_states.size(); i++)
	{
		if (this->gd->obstacle_states[i] == (int)ObstacleState::DETECTED) {
			this->gd->obstacle_states[i] = (int)ObstacleState::NOT_DESTROYED;
		}
	}
}

void Server::updateByEvent(std::unordered_map<int, std::vector<int>>events) {
	// Update timer
	if (this->gd->remaining_time >= 0) {
		this->gd->remaining_time -= TICK_TIME;
	}
	// check and update Alice's insecurity level every 30s?
	if (this->gd->remaining_time%ALERT_ALICE == 0)
	{
		this->check_A_Distance();
	}
	// Update obs cd
	updateObstacleCountdown();

	// Update skill cd
	updateSkillCD();

	std::vector<glm::mat4> playersLoc = this->gd->getAllLocations();
	for (auto it:events)
	{
		int id = it.first;
		// Not updating location if attacking
		if (this->gd->player_status[id] == (int)PlayerStatus::ATTACK) {
			continue;
		}
		std::vector<int> record = it.second;
		for (int i = 0; i < record.size(); i++)
		{
			if (record[i]) updateBySingleEvent((EventType)(i+1), id);
		}
	}
	std::vector<bool> collidingPlayer = this->collisionDetection.collideBetweenCircles(this->gd->getAllLocations());

	if (collidingPlayer[1]) {
		this->gd->location_B = playersLoc[1];
	}
	if (collidingPlayer[2]) {
		this->gd->location_C = playersLoc[2];
	}
	if (collidingPlayer[3]) {
		this->gd->location_D = playersLoc[3];
	}
}

void Server::updateInsecurity(int increase) {
	if (gd->level_A < MAX_INSECURE) {
		gd->level_A += increase;
	}
}

void Server::check_A_Distance() {
	float* aSrc = (float*)glm::value_ptr(gd->location_A);
	float* bSrc = (float*)glm::value_ptr(gd->location_B);
	float* cSrc = (float*)glm::value_ptr(gd->location_C);
	float* dSrc = (float*)glm::value_ptr(gd->location_D);

	glm::vec2 a(aSrc[12], aSrc[14]);
	glm::vec2 b(bSrc[12], bSrc[14]);
	glm::vec2 c(cSrc[12], cSrc[14]);
	glm::vec2 d(dSrc[12], dSrc[14]);

	float dists[3] = {
		glm::length(b - a),
		glm::length(c - a),
		glm::length(d - a)
	};

	float min_dist = dists[0];

	if (dists[1] < min_dist) min_dist = dists[1];
	if (dists[2] < min_dist) min_dist = dists[2];

	if (min_dist > Constants::DIST_LIMIT) { 
		updateInsecurity(1); 
	}
}

void Server::checkGameEndLogic() {
	// game time ends
	if (this->gd->remaining_time <= 0) {
		this->gd->gamestate = GameState::LOSE;
		return;
	}

	// Alice insecurity level too high
	if (this->gd->level_A >= MAX_INSECURE) {
		this->gd->gamestate = GameState::LOSE;
		return;
	}

	// check whether Alice reaches a specific tile
	int map_id = -1;
	float x = -1;
	float y = -1;
	this->map->getPosition(this->gd->location_A, &map_id, &x, &y);
	if (map_id == 2 && x >= 0 && x <= 1.0f && y >= 0 && y <= 1.0f) {
		this->gd->gamestate = GameState::WIN;
		return;
	}
}

void Server::broadcast_button_assignment()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (sessions[i] != INVALID_SOCKET)
		{
			Packet::serializeButtonAssignment(this->button_assignment, buffer[i]);
			if (send(sessions[i], buffer[i], 512, 0) == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(sessions[i]);
			}
		}
	}
}

int Server::handle_acq(int client)
{
	if (this->ids[client] != -1) // already got a character
	{
		return -1;
	}
	if (recv(sessions[client], buffer[client], 512, 0) <= 0)
		return -1;
	int character = (int)(buffer[client][0] - '0');
	if (this->button_assignment[client] == -1)
	{
		std::cout << client << " is trying to acquire " << character << std::endl;
		this->button_assignment[client] = character;
		this->ids[client] = character;
		this->broadcast_button_assignment();
		return character;
	}
	return -1;
}

void Server::handleBCDskill(int id)
{
	if (this->gd->skill_cd[id] == 0) // Skill ready!
	{
		this->gd->player_status[id] = (int)PlayerStatus::SKILL;
		this->gd->skill_cd[id] = SKILL_CD;
	}
}

void Server::updateSkillCD()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (this->gd->skill_cd[i] > 0) {
			this->gd->skill_cd[i] -= TICK_TIME;
			this->gd->skill_cd[i] = this->gd->skill_cd[i] < 0 ? 0 : this->gd->skill_cd[i];
		}
	}
}

void Server::cleanUpSkillStatus()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (this->gd->player_status[i] == (int)PlayerStatus::SKILL) {
			this->gd->player_status[i] = (int)PlayerStatus::NONE;
		}
	}
}

void Server::initialize_game()
{
	// Initialize map and gamedata
	map = new Map();
	glm::mat4 id_mat = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	std::vector<glm::mat4> BCDlocs = {map->getModelOnMap(id_mat, 1, 0.5f, 0.5f), map->getModelOnMap(id_mat, 0, 1.5f, 0.5f), map->getModelOnMap(id_mat, 2, 4.5f, 4.5f)};
	
	unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
	std::shuffle(BCDlocs.begin(), BCDlocs.end(), std::default_random_engine(seed));

	glm::mat4 locA = map->getModelOnMap(id_mat, 1, 3.5f, 3.5f);
	glm::mat4 locB = BCDlocs[0];
	glm::mat4 locC = BCDlocs[1];
	glm::mat4 locD = BCDlocs[2];

	this->gd = new GameData(locA, locB, locC, locD, std::vector<int>(NUM_OBSTACLE, 2), 0, 0, 0, 0, GAME_LENGTH, GameState::READY, std::vector<int>(NUM_PLAYERS, 0), std::vector<int>(NUM_PLAYERS, 0));
	this->obs_countdown = std::vector<std::pair<int, int>>(NUM_PLAYERS, std::make_pair(-1, -1));
	this->button_assignment = { -1, -1, -1, -1 };
	this->ids = { -1,-1,-1,-1 };
	this->check_event = { -1, -1, -1, -1 };
}
