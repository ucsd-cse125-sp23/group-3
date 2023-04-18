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

    public:
        Map();
        ~Map();

        void draw(const glm::mat4& viewProjMtx, GLuint shader);
        void update();
        void readWallsCoord(const char* file,std::vector<glm::vec3> &wallsmin, std::vector<glm::vec3> &wallsmax,glm::vec3 translation);
};