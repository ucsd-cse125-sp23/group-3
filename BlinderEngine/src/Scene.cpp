#include "Scene.h"

Scene::Scene()
{
	loadShaders();
	loadGameObjects();

	loadEssentials();
}

void Scene::init(int PlayID)
{
	// PlayID dependent loading area
	playerID = PlayID;
	if (playerID == 0) 
	{
		camera->setFirstperson();
	}
	lights = std::make_shared<Mult_Lights>(playerID == 0);
	lights->AddLightBCD(map->calculateBCDLightcenter());

}

void Scene::initLandingPage()
{
	loadLanding();
}

void Scene::drawLanding()
{
	landingPage->draw(*uiShader, 1.0f);
	readyBtn->draw(*uiShader, 1.0f);
}

void Scene::setEnd(bool won)
{
	if (won)
		endPage->bindTexture("./images/win.png");
	else
		endPage->bindTexture("./images/lose.png");
}

void Scene::drawEnd()
{
	endPage->draw(*uiShader, 1.0f);
}

void Scene::updateWorld()
{
	if (!Constants::offline) {
		lights->updateLightAlice(map->calculateLightcenter(playersObjects[playerID]->getModel()), true);
		camera->SetModel(playersObjects[playerID]->getModel());
		ui->setPlayerPosition(playersObjects[playerID]->getModel());

	}
	else {
		ui->setPlayerPosition(playersObjects[playerID]->getModel());
		lights->updateLightAlice(map->calculateLightcenter(playersObjects[playerID]->getModel()), true);
	}
	camera->Update();
	map->update();
}

void Scene::displayWorld(std::vector<int> os)
{
	lights->loadToUShader(shaderProgram, *camera);
	lights->loadToDShader(*dynamicShader, *camera);
	lights->loadToSShader(*staticShader, *camera);

	ui->draw(camera->GetViewProjectMtx(), *uiShader);
	map->draw(camera->GetViewProjectMtx(), shaderProgram, os);


	if (Constants::offline) {
		playersObjects[playerID]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
	}
	else {
		if (playerID == 0) {
			// Draw Alice herself
			playersObjects[playerID]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
		}
		else {
			// Draw all players except Alice
			for (int i = 1; i < 4; i++) {
				playersObjects[i]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
			}
		}

	}
	if (playerID != 0) {
		skybox->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *skyboxShader);
	}
}

void Scene::setModel(glm::mat4 model)
{
	playersObjects[playerID]->setModel(model);
}

void Scene::updateLevel(int curr)
{
	ui->changeLevelbarSizeY((float)curr / (float)Constants::MAX_LEVEL);

}

void Scene::updateTime(int curr)
{
	ui->changeTimebarSizeY((float)curr / (float)GAME_LENGTH);

}

void Scene::move()
{
	camera->SetMove(-CAMERA_SPEED);
	glm::mat4 newMVP = playersObjects[playerID]->calculateMoveMVP(-CAMERA_SPEED);
	playersObjects[playerID]->setModel(newMVP);
}

void Scene::spin(float i)
{
	camera->SetSpin(i * CAMERA_SPEED * TURNING_RATIO);
	playersObjects[playerID]->spin(i * CAMERA_SPEED * TURNING_RATIO);
}

void Scene::updateReadyBtn(const char* imagePath)
{
	readyBtn->bindTexture(imagePath);
}

void Scene::setAspect(float a)
{
	camera->SetAspect(a);
}

void Scene::resizeScene(int width, int height)
{
	if (ui != nullptr) {
		ui->setSize(width, height);
	}
	glViewport(0, 0, width, height);
	setAspect(float(width) / float(height));
}

void Scene::setUiByPlayerID(int id)
{
	ui->setUiByPlayerID(id);
}

void Scene::loadLanding()
{
	landingPage = std::make_shared<graphic2D>(2, 2, -1, -1, true);
	landingPage->bindTexture("./resources/images/test.png");

	readyBtn = std::make_shared<graphic2D>(0.2, 0.2, 0.7, -0.7, true);
	readyBtn->bindTexture("./resources/images/test.png");
}

void Scene::loadShaders()
{
	// Load Shaders
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
	if (!shaderProgram) {
		std::cerr << "Failed to initialize shader program" << std::endl;
	}
	dynamicShader = std::make_shared<DynamicShader>(Constants::dynamic_shader_vert, Constants::dynamic_shader_frag);
	staticShader = std::make_shared<StaticShader>(Constants::static_shader_vert, Constants::static_shader_frag);
	uiShader = std::make_shared<StaticShader>(Constants::ui_shader_vert, Constants::ui_shader_frag);
	skyboxShader = std::make_shared<StaticShader>("./shaders/skybox.vs", "./shaders/skybox.fs");
}

void Scene::loadGameObjects()
{
	// Initialize game character
	std::cerr << "loading Alice" << std::endl;
	daeObjectAlice = std::make_shared<DaeObject>(Constants::alice_model_path,
		Constants::alice_walking_animation_path,
		Constants::alice_action_animation_path,
		Constants::alice_scaling_factor);
	//std::cerr << "loaded Alice" << std::endl;
	//std::cerr << "loading Bob" << std::endl;
	//// HACK, using girl model and animation
	//daeObjectBob = std::make_shared<DaeObject>(Constants::alice_model_path,
	//	Constants::alice_walking_animation_path,
	//	Constants::alice_action_animation_path,
	//	Constants::alice_scaling_factor);
	//std::cerr << "loaded Bob" << std::endl;
	//std::cerr << "loading Carlo" << std::endl;
	//daeObjectCarlo = std::make_shared<DaeObject>(Constants::alice_model_path,
	//	Constants::alice_walking_animation_path,
	//	Constants::alice_action_animation_path,
	//	Constants::alice_scaling_factor);
	//std::cerr << "loaded Carlo" << std::endl;
	//std::cerr << "loading David" << std::endl;
	//daeObjectDavid = std::make_shared<DaeObject>(Constants::alice_model_path,
	//	Constants::alice_walking_animation_path,
	//	Constants::alice_action_animation_path,
	//	Constants::alice_scaling_factor);
	//std::cerr << "loaded David" << std::endl;
	playersObjects.push_back(daeObjectAlice);
	playersObjects.push_back(daeObjectAlice);
	playersObjects.push_back(daeObjectAlice);
	playersObjects.push_back(daeObjectAlice);
}

void Scene::loadEssentials()
{
	// Initialize object to render
	map = std::make_shared<Map>();

	ui = std::make_shared<UI>();
	skybox = std::make_shared<Skybox>();
	endPage = std::make_shared<graphic2D>(2, 2, -1, -1, true);
	camera = std::make_shared<Camera>();
	camera->SetAspect(float(WINDOW_WIDTH) / float(WINDOW_HEIGHT));

}

