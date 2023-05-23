#include <string>
#include <iostream>
#include "Submap.h"


Submap::Submap(std::vector<glm::vec3> wallsmin, std::vector<glm::vec3> wallsmax, glm::vec3 groundmin, glm::vec3 groundmax) {
    
    for (int i = 0; i < wallsmin.size(); i++) {
        glm::vec3 wallmin = wallsmin.at(i);
        glm::vec3 wallmax = wallsmax.at(i);
        walls.push_back(new Cube(wallmin, wallmax));
        
    }
    ground = new Cube(groundmin, groundmax);
}

Submap::~Submap() {
    delete ground;
    for (int i = 0; i < walls.size(); i++) {
        delete walls.at(i);
    }
}

void Submap::draw(const glm::mat4& viewProjMtx, GLuint shader) {
    ground->draw(viewProjMtx, shader);
    for (int i = 0; i < walls.size(); i++) {
       //walls[i]->draw(viewProjMtx, shader);
    }
}

void Submap::setModel(glm::mat4 _model) {
    model = _model;
    ground->update(_model);
    ground->setColor(glm::vec3(115/255.0f, 147 / 255.0f, 179 / 255.0f));
    for (std::vector<Cube*>::iterator it = walls.begin(); it != walls.end(); it++) {
        (*it)->setColor(glm::vec3(1.0f, 0.2f, 0.2f));
        (*it)->update(_model);
    }
}

void Submap::update() {

}
