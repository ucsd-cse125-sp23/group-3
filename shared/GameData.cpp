#include "GameData.h"
#include <iostream>

GameData::GameData() {
	// TODO: hardcode locations
	this->location_A = glm::mat4(1.0f);
	this->location_B = glm::mat4(1.0f);
	this->location_C = glm::mat4(1.0f);
	this->location_D = glm::mat4(1.0f);
	this->obstacle_states = std::vector<int>(NUM_OBSTACLE, 2);
	this->level_A = 0;
	this->level_B = 0;
	this->level_C = 0;
	this->level_D = 0;
	this->remaining_time = GAME_LENGTH;
	this->gamestate = GameState::READY;
}

GameData::GameData(glm::mat4 locA, glm::mat4 locB, glm::mat4 locC, glm::mat4 locD, std::vector<int> os, int levA, int levB, int levC, int levD, int rt, GameState gs) {
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

std::string GameData::gamestate_to_string() {
	std::stringstream result;
	std::copy(this->obstacle_states.begin(), this->obstacle_states.end(), std::ostream_iterator<int>(result, " "));
	
	return "locA: " + glm::to_string(this->location_A) + "\n"
		+ "locB: " + glm::to_string(this->location_B) + "\n"
		+ "locC: " + glm::to_string(this->location_C) + "\n"
		+ "locD: " + glm::to_string(this->location_D) + "\n"
		+ "obstacle_states: " + result.str().c_str() + "\n"
		+ "level_A: " + std::to_string(this->level_A) + "\n"
		+ "level_B: " + std::to_string(this->level_B) + "\n"
		+ "level_C: " + std::to_string(this->level_C) + "\n"
		+ "level_D: " + std::to_string(this->level_D) + "\n"
		+ "remaining_time: " + std::to_string(this->remaining_time) + "\n"
		+ "GameState: " + std::to_string((int)this->gamestate) + "\n";
}

std::vector<glm::mat4> GameData::getAllLocations() {
	return std::vector<glm::mat4>({this->location_A, this->location_B, this->location_C, this->location_D});
}