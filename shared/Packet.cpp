#include "Packet.h"

void Packet::serialize(GameData* gd, char* buffer) {

	mat2str(gd->location_A, buffer);
	mat2str(gd->location_B, buffer);
	mat2str(gd->location_C, buffer);
	mat2str(gd->location_D, buffer);
	
	vec2str(gd->obstacle_states, buffer, NUM_OBSTACLE);
	
	memcpy(buffer, &gd->level_A, sizeof(int));
	buffer += sizeof(int);
	memcpy(buffer, &gd->level_B, sizeof(int));
	buffer += sizeof(int);
	memcpy(buffer, &gd->level_C, sizeof(int));
	buffer += sizeof(int);
	memcpy(buffer, &gd->level_D, sizeof(int));
	buffer += sizeof(int);

	memcpy(buffer, &gd->remaining_time, sizeof(int));
	buffer += sizeof(int);

	memcpy(buffer, &gd->gamestate, sizeof(int));
	buffer += sizeof(int);
	
	vec2str(gd->player_status, buffer, 4);

	vec2str(gd->skill_cd, buffer, 4);
}

GameData Packet::deserializeGameData(char* buffer) {	
	glm::mat4 locA = str2mat(buffer);
	glm::mat4 locB = str2mat(buffer);
	glm::mat4 locC = str2mat(buffer);
	glm::mat4 locD = str2mat(buffer);
	
	std::vector<int> vec = str2vec(buffer, NUM_OBSTACLE);

	int level_A;
	memcpy(&level_A, buffer, sizeof(int));
	buffer += sizeof(int);
	int level_B;
	memcpy(&level_B, buffer, sizeof(int));
	buffer += sizeof(int);
	int level_C;
	memcpy(&level_C, buffer, sizeof(int));
	buffer += sizeof(int);
	int level_D;
	memcpy(&level_D, buffer, sizeof(int));
	buffer += sizeof(int);

	int remaining_time;
	memcpy(&remaining_time, buffer, sizeof(int));
	buffer += sizeof(int);

	GameState gamestate;
	memcpy(&gamestate, buffer, sizeof(int));
	buffer += sizeof(int);

	std::vector<int> ps = str2vec(buffer, 4);

	std::vector<int> cd = str2vec(buffer, 4);
	return GameData(locA, locB, locC, locD, vec, 
		level_A, level_B, level_C, level_D, remaining_time, gamestate, ps, cd);
}


void Packet::mat2str(const glm::mat4& mat4, char* &buffer) {
	const float* locPtr = (const float*)glm::value_ptr(mat4);
	for (int i = 0; i < 16; i++) {
		float f = locPtr[i];
		memcpy(buffer, &f, sizeof(float));
		buffer += sizeof(float);
	}
}
glm::mat4 Packet::str2mat(char* &buffer) {
	glm::mat4 mat;
	float* locPtr = (float*)glm::value_ptr(mat);
	for (int i = 0; i < 16; i++) {
		float f;
		memcpy(&f, buffer, sizeof(float));
		locPtr[i] = f;
		buffer += sizeof(float);
	}
	return mat;
}

void Packet::vec2str(const std::vector<int>& states, char* &buffer, int vec_length) {
	int vecSize = vec_length;
	for (int i = 0; i < vecSize; i++) {
		int num = states[i];
		memcpy(buffer, &num, sizeof(int));
		buffer += sizeof(int);
	}
	//std::cout << reinterpret_cast<void*>(buffer) << std::endl;
}

std::vector<int> Packet::str2vec(char* &buffer, int vec_length) {
	std::vector<int> vec;
	int size = vec_length;
	for (int i = 0; i < size; i++) {
		int num;
		memcpy(&num, buffer, sizeof(int));
		buffer += sizeof(int);
		vec.push_back(num);
	}
	return vec;
}

void Packet::serialize(Event* event, char* buffer){
	buffer[0] = '1'; // just in case we want to differentiate packets

	buffer[1] = (char)(event->getEventType());
}
Event Packet::deserializeEvent(char* buffer){
	return Event(EventType(buffer[1]));
}

void Packet::serialize(const std::vector<int>& eventRecord, char* buffer)
{
	vec2str(eventRecord, buffer, NUM_EVENT_TYPES);
}

std::vector<int> Packet::deserializeEventRecords(char* buffer)
{
	std::vector<int> vec = str2vec(buffer, NUM_EVENT_TYPES);
	return vec;
}

void Packet::serializeButtonAssignment(const std::vector<int>& buttonAssignment, char* buffer)
{
	vec2str(buttonAssignment, buffer, 4);
}

std::vector<int> Packet::deserializeButtonAssignment(char* buffer)
{
	std::vector<int> vec = str2vec(buffer, 4);
	return vec;
}
