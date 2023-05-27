#include "Scene.h"
#include <thread>
#include <omp.h>

Scene::Scene()
{
	loadShaders();
	loadEssentials();
	loadGameObjects();
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
	skill_for_alice = std::make_shared <AliceSkill>(lights->particles_light);
	initSignObject();
	obsS = std::make_shared<ObjObject>("./resources/objects/bowlingpin/bowlingpin.obj");
	obsM = std::make_shared<ObjObject>("./resources/objects/cage/cage_sketchfab.obj");
	obsL = std::make_shared<ObjObject>("./resources/objects/sign-skill/StopSign.obj");
}

void Scene::initLandingPage()
{
	loadLanding();
}

void Scene::drawLanding()
{
	landingPage->draw(*uiShader, 1.0f);

	/*readyBtn->draw(*uiShader, 1.0f);
	aBtn->draw(*uiShader, 1.0f);
	bBtn->draw(*uiShader, 1.0f);
	cBtn->draw(*uiShader, 1.0f);
	dBtn->draw(*uiShader, 1.0f);*/

	rbtn_vec[ready_state]->draw(*uiShader, 1.0f);
	abtn_vec[a_state]->draw(*uiShader, 1.0f);
	bbtn_vec[b_state]->draw(*uiShader, 1.0f);
	cbtn_vec[c_state]->draw(*uiShader, 1.0f);
	dbtn_vec[d_state]->draw(*uiShader, 1.0f);
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
	double newtimer = glfwGetTime();
	float dt = (newtimer - timer);
	timer = newtimer;
	if (!Constants::offline) {
		if (drawAliceParticle) {
			skill_for_alice->SetUp(playersObjects[0]->getModel());
			drawAliceParticle = false;
		}
		lights->updateLightAlice(map->calculateLightcenter(playersObjects[playerID]->getModel()), true);
		camera->SetModel(playersObjects[playerID]->getModel());
		ui->setPlayerPosition(playersObjects[playerID]->getModel());
		ui->setPlayerAlicePosition(playersObjects[0]->getModel());
	}
	else {
		ui->setPlayerPosition(playersObjects[playerID]->getModel());
		ui->setPlayerAlicePosition(playersObjects[0]->getModel());
		lights->updateLightAlice(map->calculateLightcenter(playersObjects[playerID]->getModel()), true);
	}
	skill_for_alice->update(dt);
	camera->Update();
	map->update();
}

void Scene::displayWorld(std::vector<int> os, int cd_remain)
{
	lights->loadToUShader(shaderProgram, *camera);
	lights->loadToDShader(*dynamicShader, *camera);
	lights->loadToSShader(*staticShader, *camera);


	ui->draw(camera->GetViewProjectMtx(), *uiShader, playerID, cd_remain);
	map->draw(camera->GetViewProjectMtx(), shaderProgram, os, sobs_pos, mobs_pos, lobs_pos);
	map->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);

	if (Constants::offline) {
		playersObjects[playerID]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
		//objObjectWall->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
		//objObjectCage->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
		for (int i = 0; i < sign_pos.size(); i++) {
			sign->setModel((glm::mat4)sign_pos.at(i));
			sign->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
		}
	}
	else {
		if (playerID == 0) {
			// Draw Alice herself
			playersObjects[playerID]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
			skill_for_alice->draw(*(particleShader), camera->GetViewProjectMtx());
			if (drawDaveSkill) {
				playersObjects[3]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
			}
		}
		else {
			// Draw all players except Alice
			for (int i = 1; i < 4; i++) {
				playersObjects[i]->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *dynamicShader);
			}
		}
		// draw Bob's skill
		for (int i = 0; i < sign_pos.size(); i++) {
			sign->setModel((glm::mat4)sign_pos.at(i));
			sign->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
		}
	}
	if (playerID != 0) {
		skybox->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *skyboxShader);
	}

	//std::cout << lobs_pos.size() << std::endl;
	for (auto pos : sobs_pos) {
		obsS->setModel((glm::mat4)pos);
		obsS->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
	}
	for (auto pos : mobs_pos) {
		obsM->setModel((glm::mat4)pos);
		obsM->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
	}
	for (auto pos : lobs_pos) {
		obsL->setModel((glm::mat4)pos);
		obsL->draw(camera->GetProjectMtx(), camera->GetViewMtx(), *staticShader);
	}
}

void Scene::setModel(glm::mat4 model)
{
	playersObjects[playerID]->setModel(model);
}

void Scene::updateLevel(float level)
{
	ui->changeLevelbarSizeY(level);

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
void Scene::updateCharBtn(int character, const char* imagePath) {
	//std::shared_ptr<graphic2D> charBtns[4] = { aBtn, bBtn, cBtn, dBtn };

	std::vector<std::shared_ptr<graphic2D>> charBtns[4] = { abtn_vec, bbtn_vec, cbtn_vec, dbtn_vec };
	//charBtns[character]->bindTexture(imagePath);
}

void Scene::setAspect(float a)
{
	camera->SetAspect(a);
}

void Scene::resizeScene(int width, int height)
{
	if (ui != nullptr) {
		ui->setSize(width, height, playerID);
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

	readyBtnGray = std::make_shared<graphic2D>(0.2, 0.2, 0.7, -0.7, true);
	readyBtn = std::make_shared<graphic2D>(0.2, 0.2, 0.7, -0.7, true);
	readyBtnSelected = std::make_shared<graphic2D>(0.2, 0.2, 0.7, -0.7, true);
	readyBtnGray->bindTexture("./resources/images/testS.png");
	readyBtn->bindTexture("./resources/images/test.png");
	readyBtnSelected->bindTexture("./resources/images/test2.png");
	rbtn_vec.push_back(readyBtnGray);
	rbtn_vec.push_back(readyBtn);
	rbtn_vec.push_back(readyBtnSelected);

	aBtn = std::make_shared<graphic2D>(0.2, 0.2, -0.9, -0.7, true);
	aBtnSelectedO = std::make_shared<graphic2D>(0.2, 0.2, -0.9, -0.7, true);
	aBtnSelectedU = std::make_shared<graphic2D>(0.2, 0.2, -0.9, -0.7, true);
	aBtn->bindTexture("./resources/images/test.png");
	aBtnSelectedO->bindTexture("./resources/images/test2.png");
	aBtnSelectedU->bindTexture("./resources/images/testX.png");
	abtn_vec.push_back(aBtn);
	abtn_vec.push_back(aBtnSelectedO);
	abtn_vec.push_back(aBtnSelectedU);

	bBtn = std::make_shared<graphic2D>(0.2, 0.2, -0.5, -0.7, true);
	bBtnSelectedO = std::make_shared<graphic2D>(0.2, 0.2, -0.5, -0.7, true);
	bBtnSelectedU = std::make_shared<graphic2D>(0.2, 0.2, -0.5, -0.7, true);
	bBtn->bindTexture("./resources/images/test.png");
	bBtnSelectedO->bindTexture("./resources/images/test2.png");
	bBtnSelectedU->bindTexture("./resources/images/testX.png");
	bbtn_vec.push_back(bBtn);
	bbtn_vec.push_back(bBtnSelectedO);
	bbtn_vec.push_back(bBtnSelectedU);

	cBtn = std::make_shared<graphic2D>(0.2, 0.2, -0.1, -0.7, true);
	cBtnSelectedO = std::make_shared<graphic2D>(0.2, 0.2, -0.1, -0.7, true);
	cBtnSelectedU = std::make_shared<graphic2D>(0.2, 0.2, -0.1, -0.7, true);
	cBtn->bindTexture("./resources/images/test.png");
	cBtnSelectedO->bindTexture("./resources/images/test2.png");
	cBtnSelectedU->bindTexture("./resources/images/testX.png");
	cbtn_vec.push_back(cBtn);
	cbtn_vec.push_back(cBtnSelectedO);
	cbtn_vec.push_back(cBtnSelectedU);

	dBtn = std::make_shared<graphic2D>(0.2, 0.2, 0.3, -0.7, true);
	dBtnSelectedO = std::make_shared<graphic2D>(0.2, 0.2, 0.3, -0.7, true);
	dBtnSelectedU = std::make_shared<graphic2D>(0.2, 0.2, 0.3, -0.7, true);
	dBtn->bindTexture("./resources/images/test.png");
	dBtnSelectedO->bindTexture("./resources/images/test2.png");
	dBtnSelectedU->bindTexture("./resources/images/testX.png");
	dbtn_vec.push_back(dBtn);
	dbtn_vec.push_back(dBtnSelectedO);
	dbtn_vec.push_back(dBtnSelectedU);
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
	particleShader = std::make_shared<StaticShader>("./shaders/particles.vs", "./shaders/particles.fs");
}

void Scene::loadGameObjects()
{
	objObjectCage = std::make_shared<ObjObject>("./resources/objects/cage/cage_sketchfab.obj", glm::vec3(15.0f));
	objObjectTest = std::make_shared<ObjObject>("./resources/objects/door/door.obj");
	std::fill_n(std::back_inserter(playersObjects), 4, nullptr);
	for (int i = 0; i < 4; i++) {
		playersObjects[i] = (initPlayerObject(i));
	}
	
	//objObjectWall = std::make_shared<ObjObject>("./resources/objects/damaged_wall/damaged_wall.fbx", glm::vec3(0.05f));
	timer = glfwGetTime();
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

std::shared_ptr<DaeObject> Scene::initPlayerObject(int playerID)
{
	if (0 == playerID) 
	{
		daeObjectAlice = std::make_shared<DaeObject>(Constants::alice_model_path,
			Constants::alice_walking_animation_path,
			Constants::alice_action_animation_path,
			glm::vec3(0.3f));
		//daeObjectAlice->spin(180);
		std::cerr << "loaded Alice" << std::endl;
		return daeObjectAlice;

	}
	else if (1 == playerID)
	{
		daeObjectBob = std::make_shared<DaeObject>(Constants::bob_model_path,
			Constants::bob_walking_animation_path,
			Constants::bob_action_animation_path,
			Constants::bob_scaling_factor);
		//daeObjectBob->spin(180);
		std::cerr << "loaded Bob" << std::endl;
		return daeObjectBob;

	}
	else if (2 == playerID)
	{
		daeObjectCarlo = std::make_shared<DaeObject>(Constants::carol_model_path,
			Constants::carol_walking_animation_path,
			Constants::carol_action_animation_path,
			Constants::carol_scaling_factor);
		//daeObjectCarlo->spin(180);
		std::cerr << "loaded Carlo" << std::endl;
		return daeObjectCarlo;
	}
	else if (3 == playerID)
	{
		daeObjectDavid = std::make_shared<DaeObject>(Constants::dave_model_path,
			Constants::dave_walking_animation_path,
			Constants::dave_action_animation_path,
			Constants::dave_scaling_factor);
		//daeObjectDavid->spin(180);
		std::cerr << "loaded David" << std::endl;
		return daeObjectDavid;
	}
	return nullptr;
}


void Scene::initSignObject() {
	sign = std::make_shared<ObjObject>("./resources/objects/sign-skill/StopSign.obj");
}

void Scene::setSignModel(glm::mat4 model) {
	// add one more sign position to vector for drawing
	sign_pos.push_back(model);
}
