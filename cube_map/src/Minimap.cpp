#include <string>
#include <iostream>
#include "Minimap.h"

Minimap::Minimap(float _sizeX,float _sizeY, float _positionX, float _positionY){
    minimap=new graphic2D( _sizeX, _sizeY,   _positionX,  _positionY,true);
    const char* textfile="./images/map.png";
    minimap->bindTexture(textfile);
    sizeX=_sizeX;
    sizeY=_sizeY;
    positionX=_positionX;
    positionY=_positionY;
    person=new graphic2D( 0.02*sizeX, 0.02*_sizeY,  _positionX+0.5*sizeX-0.01*sizeX,  _positionY+0.5*sizeY-0.01*sizeY,true);
    const char* persontextfile="./images/person.png";
    person->bindTexture(persontextfile);
}

Minimap::~Minimap(){

}

void Minimap::draw(const glm::mat4& viewProjMtx, Shader shader){
    minimap->draw(viewProjMtx,shader);
    person->draw(viewProjMtx,shader);
}

void Minimap::update(){
    person->update();
}

void Minimap::setPosition(glm::mat4 model){
    float *pSource = (float*)glm::value_ptr(model);
    personx=(pSource[12]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeX;
    persony=(-pSource[14]+GROUND_SIZE)/(GROUND_SIZE*2)*sizeY;
    person->setposition( 0.02*sizeX, 0.02*sizeY,  positionX+personx-0.01*sizeX,  positionY+persony-0.01*sizeY);
}