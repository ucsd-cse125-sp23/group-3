#include "FinalScene.h"

FinalScene::FinalScene(bool win,std::vector<std::shared_ptr<DaeObject>> _players) {
	backWallwin = std::make_shared<ObjObject>("./resources/objects/wall/wall3.obj", glm::vec3(1.0f));
	backWalllose = std::make_shared<ObjObject>("./resources/objects/wall/wall3.obj", glm::vec3(1.0f));
	players=_players;
	status = win;
	
	if (win) {
		players[0]->setScale(glm::vec3(0.3f));
		players[1]->setScale(glm::vec3(0.5f));
		players[2]->setScale(glm::vec3(0.15f));
		players[3]->setScale(glm::vec3(0.3f));
		for (int i = 0; i < players.size(); i++) {
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f + i * 10.0f / 3, 0.0f,0.0f));
			model=model* glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			players[i]->setModel(model);
			playertime.push_back(0.0f);
			playerAnim.push_back(false);
		}
	}
	else {
		players[0]->setScale(glm::vec3(0.6f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = model * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		players[0]->setModel(model);
		playerAnim.push_back(false);
	}
	backWallwin->setModel(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.5f, -5.0f)));
	backWalllose->setModel(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.5f, -5.0f)));
}

void FinalScene::update(float dt) {
	
	if (status) {
		for (int i = 0; i < playertime.size(); i++) {
			if (playertime[i] < 2.0f) {
				playertime[i] += dt;
				break;
			}
		}
		for (int i = 0; i < playertime.size(); i++) {
			if (playertime[i] > 2.0f&&playerAnim[i]==false) {

				players[i]->doWin();
				playerAnim[i] = true;
			}

		}
	}
	else {
		if (playerAnim[0] == false) {
			players[0]->doLose();
			playerAnim[0]=true;
		}
		
	}
	
}

void FinalScene::draw(StaticShader Sshader, DynamicShader Dshader, const glm::mat4& projection, const glm::mat4& view) {

	
	if (status) {
		for (auto player : players) {
			player->draw(projection, view, Dshader);
		}
		backWallwin->draw(projection, view, Sshader);
	}
	else {
		players[0]->draw(projection, view, Dshader);
		backWalllose->draw(projection, view, Sshader);
	}
}
