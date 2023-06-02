#include "FinalScene.h"

FinalScene::FinalScene(bool win,std::vector<std::shared_ptr<DaeObject>> players) {
	backWall = std::make_shared<ObjObject>("./resources/objects/wall/wall3.obj", glm::vec3(0.42f, 0.6f, 0.4f));
	players=players;
	status = win;
	playertime=std::vector<float>(4,0.0f);
	if (win) {
		for (int i = 0; i < players.size(); i++) {
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + i * 6.0f / 3, 0.0f, -1.0f));
			players[i]->setModel(model);
		}
	}
	else {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		players[0]->setModel(model);
	}
	backWall->setModel(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)));
}

void FinalScene::update(float dt) {
	for(int i=0;i<playertime.size();i++){
		if(playertime[i]<2.0f){
			playertime[i]+=dt;	
		}
	}
	if (win) {
		for (int i = 0; i < playertime.size(); i++) {
			if (playertime[i] > 2.0f) {
				players[i]->doWin();
			}

		}
	}
	else {
		players[0]->doLose();
	}
	
}

void FinalScene::draw(StaticShader Sshader, DynamicShader Dshader, const glm::mat4& projection, const glm::mat4& view) {

	backWall->draw(projection,view,Sshader);
	if (win) {
		for (auto player : players) {
			player->draw(projection, view, Dshader);
		}
	}
	else {
		players[0]->draw(projection, view, Dshader);
	}
}
