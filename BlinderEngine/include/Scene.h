#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Ground.h"
#include "Map.h"
#include "UI.h"
#include "Shader.h"
#include "AliceSkill.h"
#include "DaveSkill.h"
#include "core.h"
#include <vector>
#include <graphic2D.h>
#include <CollisionDetection.h>
#include "../../shared/GlobalVariables.h"
#include <Skybox.h>
#include "DynamicModel.h"
#include <StaticShader.h>
#include <Mult_Lights.h>
#include <Fog.h>

#include "ObjObject.h"
#include <animation.h>
#include <animator.h>
#include <Skybox.h>
#include <DaeObject.h>
#include <FinalScene.h>

#define CAMERA_SPEED 0.5f
#define TURNING_RATIO 20.0f

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum SceneStatus { running, ending };

class Scene
{
public:
	Scene();
	// Rendering
	void init(int PlayID);
	void initLandingPage();
	void initCover();
	void initInstruction();
	void drawLanding();
	void setEnd(bool won);
	void drawEnd();
	void updateEnd();
	void updateWorld();
	void displayWorld(std::vector<int> os, int cd_remain);
	void drawCover();
	void drawInstruction();
	void drawStory();
	void reset();
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
	void loadLanding();
	void endScene();
	void resetFog();
	void loadStory();
	void initStory(int pageId);

private:
	void loadShaders();
	void loadEssentials();
	std::shared_ptr<DaeObject> initPlayerObject(int playerID);
	void initSignObject();

public:
	// Control variables
	int playerID;
	double timer;

	bool drawDaveSkill = false;
	bool drawAliceParticle = false;
	bool loadingModel;

	int width;
	int height;
	float lastlevel;

	SceneStatus sceneStatus;


	// Object to render
	std::shared_ptr<Map> map;
	std::shared_ptr<UI> ui;
	std::shared_ptr<graphic2D> landingPage;
	std::shared_ptr<graphic2D> coverPage;
	std::shared_ptr<graphic2D> instructionPage;

	std::shared_ptr<FinalScene> endPage;

	int ready_state = 0;
	std::shared_ptr<graphic2D> readyBtnGray;
	std::shared_ptr<graphic2D> readyBtn;
	std::shared_ptr<graphic2D> readyBtnSelected;
	std::vector<std::shared_ptr<graphic2D>> rbtn_vec;

	int a_state = 0;
	std::shared_ptr<graphic2D> aBtn;
	std::shared_ptr<graphic2D> aBtnSelectedO;
	std::shared_ptr<graphic2D> aBtnSelectedU;
	std::vector<std::shared_ptr<graphic2D>> abtn_vec;
	int b_state = 0;
	std::shared_ptr<graphic2D> bBtn;
	std::shared_ptr<graphic2D> bBtnSelectedO;
	std::shared_ptr<graphic2D> bBtnSelectedU;
	std::vector<std::shared_ptr<graphic2D>> bbtn_vec;
	int c_state = 0;
	std::shared_ptr<graphic2D> cBtn;
	std::shared_ptr<graphic2D> cBtnSelectedO;
	std::shared_ptr<graphic2D> cBtnSelectedU;
	std::vector<std::shared_ptr<graphic2D>> cbtn_vec;
	int d_state = 0;
	std::shared_ptr<graphic2D> dBtn;
	std::shared_ptr<graphic2D> dBtnSelectedO;
	std::shared_ptr<graphic2D> dBtnSelectedU;
	std::vector<std::shared_ptr<graphic2D>> dbtn_vec;

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
	std::shared_ptr<ObjObject> sign;
	std::vector<glm::mat4> sign_pos;

	std::shared_ptr<ObjObject> obsS;
	std::vector<glm::mat4> sobs_pos;
	std::shared_ptr<ObjObject> obsM;
	std::vector<glm::mat4> mobs_pos;
	std::shared_ptr<ObjObject> obsL;
	std::vector<glm::mat4> lobs_pos;

	std::shared_ptr<ObjObject> target_exit;

	// Shaders
	GLuint shaderProgram;
	std::shared_ptr<DynamicShader> dynamicShader;
	std::shared_ptr<StaticShader> staticShader;
	std::shared_ptr<StaticShader> skyboxShader;
	std::shared_ptr<StaticShader> uiShader;
	std::shared_ptr<StaticShader> particleShader;
	std::shared_ptr<AliceSkill> skill_for_alice;
	std::shared_ptr<DaveSkill> skill_for_dave;

	// Essentials
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Mult_Lights> lights;
	std::shared_ptr<Fog> fog;

	// Story
	std::shared_ptr<graphic2D> story_page;

	glm::mat4 getPos() {
		return playersObjects[playerID]->getModel();
	}

	float buttons_y;
	float buttons_x_initial;
	float buttons_x_offset;
	float ready_x;
	float ready_y;
};