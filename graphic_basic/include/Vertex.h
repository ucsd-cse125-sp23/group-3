#pragma once

#include <vector>
#include "Joint.h"

class Vertex {
    private:
        glm::vec3 position;
        glm::vec3 normal;
        std::vector<Joint*> joints;
        std::vector<float> skinweights;

    public:
        Vertex(glm::vec3 newposition);
        ~Vertex();

        void setnormal(glm::vec3 newnormal);

        void addJoint(Joint* newjoint, float weight);
        glm::vec3 getposition();
        glm::vec3 getnormal();

        void update();

};