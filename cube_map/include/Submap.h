#pragma once

#include <vector>

#include "core.h"
#include "Cube.h"

class Submap {
    private:

        glm::mat4 model;
        glm::vec3 color;

        // Cube Information
        Cube* ground;
        std::vector<Cube*> walls;

    public:
        Submap(std::vector<glm::vec3> wallsmin,std::vector<glm::vec3> wallsmax,glm::vec3 groundmin,glm::vec3 groundmax);
        ~Submap();

        void draw(const glm::mat4& viewProjMtx, GLuint shader);
        void update();
        void setModel(glm::mat4 _model);
};