#include "GameData.h"

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
