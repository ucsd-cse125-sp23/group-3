#include <string>
#include <iostream>
#include "../include/Submap.h"


Submap::Submap(std::vector<glm::vec3> wallsmin, std::vector<glm::vec3> wallsmax, glm::vec3 groundmin, glm::vec3 groundmax) {
    for (int i = 0; i < wallsmin.size(); i++) {
        glm::vec3 wallmin = wallsmin.at(i);
        glm::vec3 wallmax = wallsmax.at(i);
    }
}

Submap::~Submap() {
}

void Submap::setModel(glm::mat4 _model) {
    model = _model;
}

void Submap::update() {

}