#include <string>
#include <iostream>
#include "Minimap.h"

Minimap::Minimap(float _sizeX,float _sizeY, float _positionX, float _positionY){
    minimap=new graphic2D( _sizeX, _sizeY,   _positionX,  _positionY,true);
    sizeX=_sizeX;
    sizeY=_sizeY;
    positionX=_positionX;
    positionY=_positionY;
}

Minimap::~Minimap(){

}

void Minimap::draw(const glm::mat4& viewProjMtx, Shader shader){
    minimap->draw(viewProjMtx,shader);
    person->draw(viewProjMtx,shader);
}

void Minimap::update(){

}

void setPosition(glm::mat4 model){
    float *pSource = (float*)glm::value_ptr(model);
    //personx=pSource[12];
    //persony=-pSource[14];

}