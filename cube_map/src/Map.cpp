#include <string>
#include <iostream>
#include "Map.h"


Map::Map() {
    float wallheight=2.0f;
    float groundheight=0.0f;
    std::vector<glm::vec3> wallsmin1=std::vector<glm::vec3>({glm::vec3(0.0f,groundheight,0.0f),glm::vec3(-5.0f,groundheight,0.0f)});
    std::vector<glm::vec3> wallsmax1=std::vector<glm::vec3>({glm::vec3(-5.0f,wallheight,0.2f),glm::vec3(-4.8f,wallheight,5.0f)});
    glm::vec3 groundmin1=glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 groundmax1=glm::vec3(-5.0f,-0.2f,5.0f);
    map1=new Submap(wallsmin1,wallsmax1,groundmin1,groundmax1);
    glm::mat4 trans1 = {
        {1,0,0,0},
        {0,1,0,0},
        {0.5,0,0.5*glm::sqrt(3.0f),0},
        {0,0,0,1}};
    map1->setModel(trans1);
}

Map::~Map() {
    delete map1;
}

void Map::update(){
    map1->update();
}

void Map::draw(const glm::mat4& viewProjMtx, GLuint shader){
    map1->draw(viewProjMtx,shader);
}

