#include <string>
#include "DOF.h"


DOF::DOF() {
    data=glm::vec3(0,0,0);
    min=glm::vec3(-100000,-100000,-100000);
    max=glm::vec3(100000,100000,100000);
}

DOF::~DOF() {

}

void DOF::SetValue(glm::vec3 newdata){
    this->data.x=glm::clamp(newdata.x,this->min.x,this->max.x);
    this->data.y=glm::clamp(newdata.y,this->min.y,this->max.y);
    this->data.z=glm::clamp(newdata.z,this->min.z,this->max.z);
}

void DOF::SetValueSp(float data,int idx){
    if(idx==0){
        this->data.x=glm::clamp(data,this->min.x,this->max.x);
    }else if(idx==1){
        this->data.y=glm::clamp(data,this->min.y,this->max.y);
    }else if(idx==2){
        this->data.z=glm::clamp(data,this->min.z,this->max.z);
    }
    
}
glm::vec3 DOF::GetValue(){
    return this->data;
}

void DOF::SetXMinMax(float min, float max){
    this->min.x=min;
    this->max.x=max;
}

void DOF::SetYMinMax(float min, float max){
    this->min.y=min;
    this->max.y=max;
}

void DOF::SetZMinMax(float min, float max){
    this->min.z=min;
    this->max.z=max;
}

