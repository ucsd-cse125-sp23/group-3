#include <string>
#include <iostream>
#include "Minimap.h"
#include "Constants.h"

Minimap::Minimap(float _sizeX,float _sizeY, float _positionX, float _positionY, const char* map_texture){
    minimap=new graphic2D( _sizeX, _sizeY,   _positionX,  _positionY,true);
    const char* textfile=map_texture;
    minimap->bindTexture(textfile);
    sizeX=_sizeX;
    sizeY=_sizeY;
    positionX=_positionX;
    positionY=_positionY;
    person=new graphic2D( Constants::MINIMAP_OBJECT_SIZE*sizeX, Constants::MINIMAP_OBJECT_SIZE*_sizeY,  _positionX+0.5*sizeX-Constants::MINIMAP_OBJECT_SIZE/2*sizeX,  _positionY+0.5*sizeY-Constants::MINIMAP_OBJECT_SIZE/2*sizeY,true);
    const char* persontextfile="./images/star.png";
    person->bindTexture(persontextfile);
    person2=new graphic2D( Constants::MINIMAP_OBJECT_SIZE*sizeX, Constants::MINIMAP_OBJECT_SIZE*_sizeY,  _positionX+0.5*sizeX-Constants::MINIMAP_OBJECT_SIZE/2*sizeX,  _positionY+0.5*sizeY-Constants::MINIMAP_OBJECT_SIZE/2*sizeY,true);
    persontextfile="./images/heart.png";
    person2->bindTexture(persontextfile);
    Alice_shown=false;
}

Minimap::~Minimap(){

}

void Minimap::draw(const glm::mat4& viewProjMtx, StaticShader shader){
    minimap->draw(shader, 1.0f);
    person->draw(shader, 1.0f);
    if(Alice_shown){
        person2->draw(shader, 1.0f);
    }
}

void Minimap::update(){
    minimap->update();
    person->update();
    person2->update();
}

void Minimap::setPosition(glm::mat4 model){
    float *pSource = (float*)glm::value_ptr(model);
    personx=(pSource[12]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeX;
    persony=(-pSource[14]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeY;
    person->setposition( Constants::MINIMAP_OBJECT_SIZE*sizeX, Constants::MINIMAP_OBJECT_SIZE*sizeY,  positionX+personx-Constants::MINIMAP_OBJECT_SIZE/2*sizeX,  positionY+persony-Constants::MINIMAP_OBJECT_SIZE/2*sizeY);
}

void Minimap::setPositionAlice(glm::mat4 model){
    float *pSource = (float*)glm::value_ptr(model);
    float personx2=(pSource[12]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeX;
    float persony2=(-pSource[14]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeY;
    person2->setposition( Constants::MINIMAP_OBJECT_SIZE*sizeX, Constants::MINIMAP_OBJECT_SIZE*sizeY,  positionX+personx2-Constants::MINIMAP_OBJECT_SIZE/2*sizeX,  positionY+persony2-Constants::MINIMAP_OBJECT_SIZE/2*sizeY);
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