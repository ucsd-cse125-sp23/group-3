#include "PlayerModel.h"

PlayerModel::PlayerModel(std::vector<DaeObject*> _playerModels){
    this->playerModels = _playerModels;
}

void PlayerModel::draw(const glm::mat4& projection, const glm::mat4& view, DynamicShader& shader){
    for (DaeObject* player: this->playerModels) {
        player->draw(projection, view, shader);
    }
}

void PlayerModel::update(GameData gd){
    std::vector<glm::mat4> locations = gd.getAllLocations();
    for (int i = 0; i < this->playerModels.size(); i++) {
        playerModels[i]->update(locations[i]);
    }
}
