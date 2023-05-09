#pragma once

#include <vector>

#include "core.h"

class Submap {
    private:

        glm::mat4 model;
        glm::vec3 color;


    public:
        Submap(std::vector<glm::vec3> wallsmin,std::vector<glm::vec3> wallsmax,glm::vec3 groundmin,glm::vec3 groundmax);
        ~Submap();

        glm::mat4 getModel(){return model;};
        void update();
        void setModel(glm::mat4 _model);
};