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
	lights = std::make_shared<Mult_Lights>(PlayID == 0);
	playerID = PlayID;
	if (playerID == 0)
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
	dynamicShader = std::make_shared<DynamicShader>(Constants::dynamic_shader_vert, Constants::dynamic_shader_frag);
	staticShader = std::make_shared<StaticShader>(Constants::static_shader_vert, Constants::static_shader_frag);
	uiShader = std::make_shared<StaticShader>(Constants::ui_shader_vert, Constants::ui_shader_frag);
	skyboxShader = std::make_shared<StaticShader>("./shaders/skybox.vs", "./shaders/skybox.fs");
}

void Scene::loadGameObjects()
{
	// Initialize object to render
	map = std::make_shared<Map>();
	ui = std::make_shared<UI>();
	skybox = std::make_shared<Skybox>();
	endPage = std::make_shared<graphic2D>(2, 2, -1, -1, true);


	for (int i = 0; i < 4; i++) {
		Cube* temp = new Cube();
		players.at(i) = temp;
	}

	// Initialize game character
	daeObjectAlice = std::make_shared<DaeObject>(Constants::alice_model_path,
		Constants::alice_walking_animation_path,
		Constants::alice_action_animation_path,
		Constants::alice_scaling_factor);

	// HACK, using girl model and animation
	daeObjectBob = std::make_shared<DaeObject>(Constants::girl_model_path,
		Constants::girl_walking_animation_path,
		Constants::girl_action_animation_path,
		Constants::girl_scaling_factor);

	daeObjectCarlo = std::make_shared<DaeObject>(Constants::girl_model_path,
		Constants::girl_walking_animation_path,
		Constants::girl_action_animation_path,
		Constants::girl_scaling_factor);

	daeObjectDavid = std::make_shared<DaeObject>(Constants::girl_model_path,
		Constants::girl_walking_animation_path,
		Constants::girl_action_animation_path,
		Constants::girl_scaling_factor);

	playersObjects.push_back(daeObjectAlice);
	playersObjects.push_back(daeObjectBob);
	playersObjects.push_back(daeObjectCarlo);
	playersObjects.push_back(daeObjectDavid);
}

void Scene::loadEssentials()
{
	camera = std::make_shared<Camera>();
}

