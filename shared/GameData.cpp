#include "GameData.h"
#include <iostream>

GameData::GameData() {
	// TODO: hardcode locations
	this->obstacle_states = vector<int>(NUM_OBSTACLE, 2);
	this->level_A = 0;
	this->level_B = 0;
	this->level_C = 0;
	this->level_D = 0;
	this->remaining_time = GAME_LENGTH;
	this->gamestate = GameState::READY;
}

GameData::GameData(glm::mat4 locA) {
	this->location_A = locA;
}

GameData::GameData(glm::mat4 locA, glm::mat4 locB, glm::mat4 locC, glm::mat4 locD, vector<int> os, int levA, int levB, int levC, int levD, int rt, GameState gs) {
	this->location_A = locA;
	this->location_B = locB;
	this->location_C = locC;
	this->location_D = locD;
	this->obstacle_states = os;
	this->level_A = levA;
	this->level_B = levB;
	this->level_C = levC;
	this->level_D = levD;
	this->remaining_time = rt;
	this->gamestate = gs;
}

<<<<<<< Updated upstream:shared/GameData.cpp
=======
void GameData::serialize(GameData* gd, char* buffer) {

	mat2str(gd->location_A, buffer);
	mat2str(gd->location_B, buffer);
	mat2str(gd->location_C, buffer);
	mat2str(gd->location_D, buffer);
	
	vec2str(gd->obstacle_states, buffer);
	
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
	
	//memcpy(buffer, '\0', 1);
	// buffer = '\0';
}
/*
	@return: should delete returned GameData ptr 
*/
GameData GameData::deserialize(char* buffer) {	
	glm::mat4 locA = str2mat(buffer);
	glm::mat4 locB = str2mat(buffer);
	glm::mat4 locC = str2mat(buffer);
	glm::mat4 locD = str2mat(buffer);
	
	vector<int> vec = str2vec(buffer);

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

	return GameData(locA, locB, locC, locD, vec, 
		level_A, level_B, level_C, level_D, remaining_time, gamestate);
}


void GameData::mat2str(const glm::mat4& mat4, char* &buffer) {
	const float* locPtr = (const float*)glm::value_ptr(mat4);
	for (int i = 0; i < 16; i++) {
		float f = locPtr[i];
		memcpy(buffer, &f, sizeof(float));
		buffer += sizeof(float);
	}
}
glm::mat4 GameData::str2mat(char* &buffer) {
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

void GameData::vec2str(const vector<int>& states, char* &buffer) {
	int vecSize = states.size();
	cout << reinterpret_cast<void*>(buffer) << endl;
	memcpy(buffer, &vecSize, sizeof(int));
	buffer += sizeof(int);
	for (int i = 0; i < vecSize; i++) {
		int num = states[i];
		memcpy(buffer, &num, sizeof(int));
		buffer += sizeof(int);
	}
	cout << reinterpret_cast<void*>(buffer) << endl;
}

vector<int> GameData::str2vec(char* &buffer) {
	vector<int> vec;
	int size;
	memcpy(&size, buffer, sizeof(int));
	buffer += sizeof(int);
	for (int i = 0; i < size; i++) {
		int num;
		memcpy(&num, buffer, sizeof(int));
		buffer += sizeof(int);
		vec.push_back(num);
	}
	return vec;
}

>>>>>>> Stashed changes:shared/GameStates/GameData.cpp
string GameData::gamestate_to_string() {
	stringstream result;
	copy(this->obstacle_states.begin(), this->obstacle_states.end(), std::ostream_iterator<int>(result, " "));
	
	return "locA: " + glm::to_string(this->location_A) + "\n"
		+ "locB: " + glm::to_string(this->location_B) + "\n"
		+ "locC: " + glm::to_string(this->location_C) + "\n"
		+ "locD: " + glm::to_string(this->location_D) + "\n"
		+ "obstacle_states: " + result.str().c_str() + "\n"
		+ "level_A: " + to_string(this->level_A) + "\n"
		+ "level_B: " + to_string(this->level_B) + "\n"
		+ "level_C: " + to_string(this->level_C) + "\n"
		+ "level_D: " + to_string(this->level_D) + "\n"
		+ "remaining_time: " + to_string(this->remaining_time) + "\n"
		+ "GameState: " + to_string((int)this->gamestate) + "\n";
}