#include "Vertex.h"
#include <iostream>

Vertex::Vertex(glm::vec3 newposition) {
    normal=glm::vec3(0,0,0);
    position=newposition;
    joints = std::vector<Joint*>();
    skinweights= std::vector<float>();
}
   

Vertex::~Vertex() {
    
}

void Vertex::setnormal(glm::vec3 newnormal){
    normal=newnormal;
}

void Vertex::addJoint(Joint* newjoint,float weight ){
    joints.push_back(newjoint);
    skinweights.push_back(weight);
}

glm::vec3 Vertex::getposition(){
    glm::vec4 newposition=glm::vec4(0.0,0.0,0.0,0);
    //std::cout<<glm::to_string(position)<<std::endl;
    glm::vec4 homopos=glm::vec4(position.x,position.y,position.z,1);
    int i=0;
    for (std:: vector<Joint*>::iterator it = joints.begin(); it != joints.end(); it++){
        //std::cout<<glm::to_string((*it)->getBind())<<std::endl;
        newposition=newposition+skinweights.at(i)*(((*it)->getBind())*homopos);
        i++;
    }
    //std::cout<<newposition.x<<newposition.y<<newposition.z<<std::endl;
    return glm::vec3(newposition.x,newposition.y,newposition.z);
}

glm::vec3 Vertex::getnormal(){
    glm::vec4 newposition=glm::vec4(0.0,0.0,0.0,0);
    glm::vec4 homopos=glm::vec4(normal.x,normal.y,normal.z,0);
    int i=0;
    for (std:: vector<Joint*>::iterator it = joints.begin(); it != joints.end(); it++){
        newposition=newposition+skinweights.at(i)*(glm::transpose(glm::inverse((*it)->getBind())))*homopos;
        i++;
    }
    return glm::normalize(glm::vec3(newposition.x,newposition.y,newposition.z));
}

void Vertex::update(){
    return;
}