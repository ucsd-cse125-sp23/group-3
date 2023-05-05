#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>
#include <sstream>
#include "GlobalVariables.h"

class GameData {
public:
	GameData();
	GameData(glm::mat4 locA, glm::mat4 locB, glm::mat4 locC, glm::mat4 locD, std::vector<int> os, int levA, int levB, int levC, int levD, int rt, GameState gs, std::vector<int> ps);

	std::vector<glm::mat4> getAllLocations();

	std::string gamestate_to_string();

	glm::mat4 location_A;
	glm::mat4 location_B;
	glm::mat4 location_C;
	glm::mat4 location_D;
	std::vector<int> obstacle_states;
	int level_A;
	int level_B;
	int level_C;
	int level_D;
	int remaining_time; // in ms
	GameState gamestate;
	std::vector<int> player_status;
};