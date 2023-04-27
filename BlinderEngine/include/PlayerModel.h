#pragma once
#include "DaeObject.h"
#include "../../shared/GameData.h"
#include <vector>

class PlayerModel
{
public:
	PlayerModel(std::vector<DaeObject*> _playerModels);

	void draw(const glm::mat4& projection, const glm::mat4& view, DynamicShader& shader);

	void update(GameData gd);

private:
	vector<DaeObject*> playerModels;
};