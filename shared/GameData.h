#include <glm/glm.hpp>
#include <vector>
#include "GlobalVariables.h"
using namespace std;

class GameData {
public:
	GameData();
	GameData(glm::mat4 locA); // testing constructor
	GameData(glm::mat4 locA, glm::mat4 locB, glm::mat4 locC, glm::mat4 locD, vector<int> os, int levA, int levB, int levC, int levD, int rt, GameState gs);

protected:
	glm::mat4 location_A;
	glm::mat4 location_B;
	glm::mat4 location_C;
	glm::mat4 location_D;
	vector<int> obstacle_states;
	int level_A;
	int level_B;
	int level_C;
	int level_D;
	int remaining_time; // in seconds?
	GameState gamestate;
};