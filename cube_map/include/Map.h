#pragma once

#include <vector>

#include "core.h"
#include "Cube.h"
#include "Submap.h"

class Map {
    private:

        glm::mat4 model;
        Submap* map1;
        Submap* map2;
        Submap* map3;

    public:
        Map();
        ~Map();

        void draw(const glm::mat4& viewProjMtx, GLuint shader);
        void update();
};