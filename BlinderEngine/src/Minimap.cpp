#include <string>
#include <iostream>
#include "Minimap.h"
#include "Constants.h"

Minimap::Minimap(float _sizeX,float _sizeY, float _positionX, float _positionY){
    minimap=new graphic2D( _sizeX, _sizeY,   _positionX,  _positionY,true);
    const char* textfile="./images/map.png";
    minimap->bindTexture(textfile);
    sizeX=_sizeX;
    sizeY=_sizeY;
    positionX=_positionX;
    positionY=_positionY;
    person=new graphic2D( Constants::MINIMAP_OBJECT_SIZE*sizeX, Constants::MINIMAP_OBJECT_SIZE*_sizeY,  _positionX+0.5*sizeX-Constants::MINIMAP_OBJECT_SIZE/2*sizeX,  _positionY+0.5*sizeY-Constants::MINIMAP_OBJECT_SIZE/2*sizeY,true);
    const char* persontextfile="./images/person.png";
    person->bindTexture(persontextfile);
}

Minimap::~Minimap(){

}

void Minimap::draw(const glm::mat4& viewProjMtx, StaticShader shader){
    minimap->draw(shader);
    person->draw(shader);
}

void Minimap::update(){
    minimap->update();
    person->update();
}

void Minimap::setPosition(glm::mat4 model){
    float *pSource = (float*)glm::value_ptr(model);
    personx=(pSource[12]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeX;
    persony=(-pSource[14]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeY;
    person->setposition( Constants::MINIMAP_OBJECT_SIZE*sizeX, Constants::MINIMAP_OBJECT_SIZE*sizeY,  positionX+personx-Constants::MINIMAP_OBJECT_SIZE/2*sizeX,  positionY+persony-Constants::MINIMAP_OBJECT_SIZE/2*sizeY);
}

graphic2D* Minimap::getMinimap() {
    return minimap;
}

void Minimap::setposition(float _sizeX, float _sizeY, float _positionX, float _positionY) {
    this->minimap->setposition(_sizeX, _sizeY, _positionX, _positionY);
    sizeX = _sizeX;
    sizeY = _sizeY;
    positionX = _positionX;
    positionY = _positionY;
}