#pragma once
#include <core.h>
#include "DaeObject.h"
#include <DynamicShader.h>
#include <StaticShader.h>
#include <DynamicModel.h>
#include "../../shared/GameData.h"
#include <vector>
using namespace std;

class PlayerModel
{
public:
	PlayerModel();

	void draw(const glm::mat4& projection, const glm::mat4& view, DynamicShader& shader);

	void update(GameData gd);

private:
	vector<DaeObject*> playerModels;

	glm::mat4 location_A;
	glm::mat4 location_B;
	glm::mat4 location_C;
	glm::mat4 location_D;
};