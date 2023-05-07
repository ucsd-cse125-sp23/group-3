#include "Mult_Lights.h"
#include <string>
#include <cstring>

Mult_Lights::Mult_Lights(bool _player0){
    Alice=_player0;
    Light* spotLight=new Light(true,false,glm::vec3(1.0f), glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0.0f,30.0f,0.0f),0.1f, 0.7f,  0.2f);
    spotLight->SetParam(1.0f,0.09f,0.032f);
    spotLight->SetSpot(12.5f,15.0f);
}

Mult_Lights::~Mult_Lights(){

}

void Mult_Lights::loadToDShader(DynamicShader& shader,Camera& cam){
    shader.use();
    shader.setVec3("viewPos", cam.CameraPos);
    if(Alice){
        int num_light=0;
        for(int i=0;i<lights_for_A.size();i++){
            Light* temp=lights_for_A[i];
            if(temp->spotLight){
                shader.setVec3("spotLight.position", temp->position);
                shader.setVec3("spotLight.direction", temp->direction);
                shader.setVec3("spotLight.ambient", temp->ambient*(temp->lightcolor));
                shader.setVec3("spotLight.diffuse", temp->diffuse*(temp->lightcolor));
                shader.setVec3("spotLight.specular", temp->specular*(temp->lightcolor));
                shader.setFloat("spotLight.constant", temp->constant);
                shader.setFloat("spotLight.linear", temp->linear);
                shader.setFloat("spotLight.quadratic", temp->quadratic);
                shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(temp->cutoff)));
                shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(temp->outerCutOff)));  
            }
            else if(temp->pointLight){
                std::string Lightpos="pointLights["+std::to_string(num_light)+"]";
                shader.setVec3((Lightpos+".position").c_str(), temp->position);
                shader.setVec3((Lightpos+".ambient").c_str(), temp->ambient*(temp->lightcolor));
                shader.setVec3((Lightpos+".diffuse").c_str(), temp->diffuse*(temp->lightcolor));
                shader.setVec3((Lightpos+".specular").c_str(), temp->specular*(temp->lightcolor));
                shader.setFloat((Lightpos+".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos+".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos+".quadratic").c_str(), temp->quadratic);
                num_light++;
            }else{
                shader.setVec3("dirLight.direction", temp->direction);
                shader.setVec3("dirLight.ambient", temp->ambient*(temp->lightcolor));
                shader.setVec3("dirLight.diffuse", temp->diffuse*(temp->lightcolor));
                shader.setVec3("dirLight.specular", temp->specular*(temp->lightcolor));
            }
        }
    }
    else{
        int num_light=0;
        for(int i=0;i<lights_for_BCD.size();i++){
            Light* temp=lights_for_BCD[i];
            if(temp->spotLight){
                shader.setVec3("spotLight.position", temp->position);
                shader.setVec3("spotLight.direction", temp->direction);
                shader.setVec3("spotLight.ambient", temp->ambient*(temp->lightcolor));
                shader.setVec3("spotLight.diffuse", temp->diffuse*(temp->lightcolor));
                shader.setVec3("spotLight.specular", temp->specular*(temp->lightcolor));
                shader.setFloat("spotLight.constant", temp->constant);
                shader.setFloat("spotLight.linear", temp->linear);
                shader.setFloat("spotLight.quadratic", temp->quadratic);
                shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(temp->cutoff)));
                shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(temp->outerCutOff)));  
            }
            else if(temp->pointLight){
                std::string Lightpos="pointLights["+std::to_string(num_light)+"]";
                shader.setVec3((Lightpos+".position").c_str(), temp->position);
                shader.setVec3((Lightpos+".ambient").c_str(), temp->ambient*(temp->lightcolor));
                shader.setVec3((Lightpos+".diffuse").c_str(), temp->diffuse*(temp->lightcolor));
                shader.setVec3((Lightpos+".specular").c_str(), temp->specular*(temp->lightcolor));
                shader.setFloat((Lightpos+".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos+".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos+".quadratic").c_str(), temp->quadratic);
                num_light++;
            }else{
                shader.setVec3("dirLight.direction", temp->direction);
                shader.setVec3("dirLight.ambient", temp->ambient*(temp->lightcolor));
                shader.setVec3("dirLight.diffuse", temp->diffuse*(temp->lightcolor));
                shader.setVec3("dirLight.specular", temp->specular*(temp->lightcolor));
            }
        }
    }
}

void Mult_Lights::loadToSShader(StaticShader& shader,Camera& cam){

}