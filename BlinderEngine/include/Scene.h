#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Ground.h"
#include "Map.h"
#include "UI.h"
#include "Shader.h"
#include "AliceSkill.h"
#include "core.h"
#include <vector>
#include <graphic2D.h>
#include <CollisionDetection.h>
#include "../../shared/GlobalVariables.h"
#include <Skybox.h>
#include "DynamicModel.h"
#include <StaticShader.h>
#include <Mult_Lights.h>

#include "ObjObject.h"
#include <animation.h>
#include <animator.h>
#include <Skybox.h>
#include <DaeObject.h>

#define CAMERA_SPEED 1.5f
#define TURNING_RATIO 20.0f

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


class Scene
{
public:
	Scene();
	// Rendering
	void init(int PlayID);
	void initLandingPage();
	void drawLanding();
	void setEnd(bool won);
	void drawEnd();
	void updateWorld();
	void displayWorld(std::vector<int> os);
	// Control
	void setModel(glm::mat4 model);
	void updateLevel(float level);
	void updateTime(int curr);
	void move();
	void spin(float i);
	void updateReadyBtn(const char* imagePath);
	void updateCharBtn(int character, const char* imagePath);
	void setAspect(float a);
	void resizeScene(int width, int height);
	void setUiByPlayerID(int id);
	void loadGameObjects();
	void setSignModel(glm::mat4 model);

private:
	void loadLanding();
	void loadShaders();
	void loadEssentials();
	std::shared_ptr<DaeObject> initPlayerObject(int playerID);
	void initSignObject();

public:
	// Control variables
	int playerID;
	double timer;
	// Object to render
	std::shared_ptr<Map> map;
	std::shared_ptr<UI> ui;
	std::shared_ptr<graphic2D> landingPage;
	std::shared_ptr<graphic2D> readyBtn;
	std::shared_ptr<graphic2D> aBtn;
	std::shared_ptr<graphic2D> bBtn;
	std::shared_ptr<graphic2D> cBtn;
	std::shared_ptr<graphic2D> dBtn;
	std::shared_ptr<graphic2D> endPage;
	std::shared_ptr<Skybox> skybox;
	std::vector<std::shared_ptr<DaeObject>> playersObjects;
	std::shared_ptr<DaeObject> daeObjectAlice;
	std::shared_ptr<DaeObject> daeObjectBob;
	std::shared_ptr<DaeObject> daeObjectCarlo;
	std::shared_ptr<DaeObject> daeObjectDavid;
	std::shared_ptr<ObjObject> objObjectWall;
	std::shared_ptr<ObjObject> objObjectCage;
	std::shared_ptr<ObjObject> objObjectTest;
	std::vector<std::shared_ptr<ObjObject>> signs;

	// Shaders
	GLuint shaderProgram;
	std::shared_ptr<DynamicShader> dynamicShader;
	std::shared_ptr<StaticShader> staticShader;
	std::shared_ptr<StaticShader> skyboxShader;
	std::shared_ptr<StaticShader> uiShader;
	std::shared_ptr<StaticShader> particleShader;
	std::shared_ptr<AliceSkill> skill_for_alice;
	// Essentials
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Mult_Lights> lights;
};