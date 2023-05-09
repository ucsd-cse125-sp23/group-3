#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Ground.h"
#include "Map.h"
#include "UI.h"
#include "Shader.h"
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


class Scene
{
public:
	Scene();
	void init(int PlayID);
	void drawLanding();
	void setEnd(bool win);
	void drawEnd();

private:
	void loadLanding();
	void loadShaders();
	void loadGameObjects();
	void loadEssentials();

public:
	// Control variables
	int playerID;

	// Object to render
	std::shared_ptr<Map> map;
	std::vector<Cube*> players;
	std::shared_ptr<UI> ui;
	std::shared_ptr<graphic2D> landingPage;
	std::shared_ptr<graphic2D> readyBtn;
	std::shared_ptr<graphic2D> endPage;
	std::shared_ptr<Skybox> skybox;
	std::vector<std::shared_ptr<DaeObject>> playersObjects;
	std::shared_ptr<DaeObject> daeObjectAlice;
	std::shared_ptr<DaeObject> daeObjectBob;
	std::shared_ptr<DaeObject> daeObjectCarlo;
	std::shared_ptr<DaeObject> daeObjectDavid;

	// Shaders
	GLuint shaderProgram;
	std::shared_ptr<DynamicShader> dynamicShader;
	std::shared_ptr<StaticShader> staticShader;
	std::shared_ptr<StaticShader> skyboxShader;
	std::shared_ptr<StaticShader> uiShader;

	// Essentials
	std::shared_ptr<Camera*> camera;
	std::shared_ptr<Mult_Lights*> lights;
};