#pragma once

#include <vector>

#include "core.h"
#include "Cube.h"
#include "Submap.h"
#include "Tokenizer.h"

class Map {
private:

    glm::mat4 model;
    Submap* map1;
    Submap* map2;
    Submap* map3;
    float wallheight, groundheight, wallwidth, groundsize;
    int mapEncode[3][6][6];

public:
    Map();
    ~Map();

    void draw(const glm::mat4& viewProjMtx, GLuint shader);
    void getPosition(glm::mat4 model, int* mapID, float* x, float* y);
    void update();
    void readWallsCoord(int mapId, const char* file, std::vector<glm::vec3>& wallsmin, std::vector<glm::vec3>& wallsmax, glm::vec3 translation);
};