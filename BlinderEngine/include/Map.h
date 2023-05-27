#pragma once

#include <vector>
#include <utility>
#include "core.h"
#include "Cube.h"
#include "Submap.h"
#include "Tokenizer.h"
#include "Obstacles.h"
#include "ObjObject.h"
#include "StaticShader.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

class Map {
private:
    std::shared_ptr<ObjObject> objObjectWall;
    glm::mat4 model;
    Submap* map1;
    Submap* map2;
    Submap* map3;
    float wallheight, groundheight, wallwidth, groundsize;
    std::vector<std::tuple<int, float, float>> walls;
    std::vector<bool> walls_left_top;

public:
    Map();
    ~Map();

    void draw(const glm::mat4& viewProjMtx, GLuint shader, std::vector<int> os, std::vector<glm::mat4>& sobs_pos, std::vector<glm::mat4>& mobs_pos, std::vector<glm::mat4>& lobs_pos);
    void draw(const glm::mat4& projection, const glm::mat4& view, StaticShader& shader);
    void getPosition(glm::mat4& model, int* mapID, float* x, float* y);
    std::vector<std::pair<float, float>> getGrid(int mapID, float x, float y);
    glm::vec4 getPointsCollision(int mapID, float x, float y);
    glm::mat4 getModelOnMap(glm::mat4& original, int mapID, float x, float y);
    void update();
    void readWallsCoord(int mapId, const char* file, std::vector<glm::vec3>& wallsmin, std::vector<glm::vec3>& wallsmax, glm::vec3 translation);
    glm::vec3 calculateLightcenter(glm::mat4 model);
    std::vector<glm::vec3> calculateBCDLightcenter();

    Obstacles* obs;
};