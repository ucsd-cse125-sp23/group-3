#include "Keyframe.h"
/* lookup table for rules of tangents:
0:fixed
1:flat
2:linear
3:smooth
 */
Keyframe::Keyframe(float time, float value,int rulein,int ruleout,float tanin,float tanout){
    this->Time=time;
    this->Value=value;
    this->RuleIn=rulein;
    this->RuleOut=ruleout;
    if(rulein==0){
        this->TangentIn=tanin;
    }
    if(ruleout==0){
        this->TangentOut=tanout;
    }
    this->lastframe=NULL;
    this->nextframe=NULL;
    this->coeffs=glm::vec4();
}

Keyframe::~Keyframe(){
    delete lastframe;
    delete nextframe;
}

void Keyframe::setLast(Keyframe* lastFrame){
    this->lastframe=lastFrame;
}

void Keyframe::setNext(Keyframe* nextFrame){
    this->nextframe=nextFrame;
}

void Keyframe::computeTangents(){
    switch(RuleIn){
        case 1:
            this->TangentIn=0;
            break;
        case 2:
            if(this->lastframe!=NULL){
                this->TangentIn=(this->Value-this->lastframe->Value)/(this->Time-this->lastframe->Time);
            }
            else{
                this->TangentIn=0;
            }
            break;
        case 3:
            if(this->lastframe==NULL&&this->nextframe==NULL){
                this->TangentIn=0;
            }
            else if(this->nextframe==NULL){
                this->TangentIn=(this->Value-this->lastframe->Value)/(this->Time-this->lastframe->Time);
            }
            else if(this->lastframe==NULL){
                this->TangentIn=0;
            }
            else{
                this->TangentIn=(this->nextframe->Value-this->lastframe->Value)/(this->nextframe->Time-this->lastframe->Time);
            }
            break;
        default:
            break;

    }
    switch(RuleOut){
        case 1:
            this->TangentOut=0;
            break;
        case 2:
            if(this->nextframe!=NULL){
                this->TangentOut=(this->nextframe->Value-this->Value)/(this->nextframe->Time-this->Time);
            }
            else{
                this->TangentOut=0;
            }
            break;
        case 3:
            if(this->lastframe==NULL&&this->nextframe==NULL){
                this->TangentOut=0;
            }
            else if(this->lastframe==NULL){
                this->TangentOut=(this->nextframe->Value-this->Value)/(this->nextframe->Time-this->Time);
            }
            else if(this->nextframe==NULL){
                this->TangentOut=0;
            }
            else{
                this->TangentOut=(this->nextframe->Value-this->lastframe->Value)/(this->nextframe->Time-this->lastframe->Time);
            }
            break;
        default:
            break;

    }  
}

void Keyframe::computeCoeffcients(){
    
    //std::cout<<"tanout"<<this->getTanIn()<<std::endl;
    //std::cout<<"tanout"<<this->getTanOut()<<std::endl;
    if(this->nextframe!=NULL){
        //std::cout<<"nextval"<<this->nextframe->Value<<std::endl;
        glm::mat4 trans = {
        {2,-2,1,1},
        {-3,3,-2,-1},
        {0,0,1,0},
        {1,0,0,0}};
        //std::cout<<"trans mat"<<glm::to_string(trans)<<std::endl;
        float timerange=this->nextframe->getTime()-this->getTime();
        glm::vec4 pv=glm::vec4(this->Value,this->nextframe->Value,timerange*this->getTanOut(),timerange*this->nextframe->getTanIn());
        //std::cout<<this->getTanOut()<<std::endl;
        this->coeffs=glm::transpose(trans)*pv;
    } 
}

float Keyframe::getTime(){
    return this->Time;
}

float Keyframe::getValue(){
    return this->Value;
}

float Keyframe::getTanIn(){
    return this->TangentIn;
}

float Keyframe::getTanOut(){
    return this->TangentOut;
}

glm::vec4 Keyframe::getCoef(){
    return this->coeffs;
}
