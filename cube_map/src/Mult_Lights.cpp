#include "Mult_Lights.h"
#include <string>
#include <cstring>

/*
 Light class::bool _spotLight,
 bool _pointLight,
 glm::vec3 _color, 
 glm::vec3 _direction, 
 glm::vec3 _position, 
 float _ambient, 
 float _diffuse, 
 float _specular
*/
Mult_Lights::Mult_Lights(bool _player0){
    Alice=_player0;
    Light* spotLight=new Light(true,false,glm::vec3(1.0f), glm::vec3(0.1f,-1.0f,0.0f), glm::vec3(0.0f,5.0f,0.0f),0.3f, 1.1f,  0.2f);
    spotLight->SetParam(1.0f,0.09f,0.032f);
    spotLight->SetSpot(25.0f,30.0f);
    lights_for_A.push_back(spotLight);

    Light* dirLight=new Light(false,false,glm::vec3(0.5f), glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0.0f,5.0f,0.0f),0.1f, 0.3f,  0.0f);
    lights_for_A.push_back(dirLight);
}

Mult_Lights::~Mult_Lights(){

}
/*
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
        shader.setInt("NUM_LIGHTS",num_light);
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
        shader.setInt("NUM_LIGHTS",num_light);
    }
}

void Mult_Lights::loadToSShader(StaticShader& shader,Camera& cam){

}
*/

void Mult_Lights::loadToUShader(GLuint shader,Camera& cam){
    glUseProgram(shader);
    glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, &cam.CameraPos[0]);
    if(Alice){
        int num_light=0;
        for(int i=0;i<lights_for_A.size();i++){
            Light* temp=lights_for_A[i];
            //std::cout<<lights_for_A.size()<<std::endl;
            if(temp->spotLight){
                glUniform3fv(glGetUniformLocation(shader, "spotLight.position"),1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.direction"),1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.ambient"),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.diffuse"),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.specular"),1, &(temp->specular*(temp->lightcolor))[0]);

                glUniform1f(glGetUniformLocation(shader, "spotLight.constant"),temp->constant);
                glUniform1f(glGetUniformLocation(shader, "spotLight.linear"),temp->linear);
                glUniform1f(glGetUniformLocation(shader, "spotLight.quadratic"),temp->quadratic);
                glUniform1f(glGetUniformLocation(shader, "spotLight.cutOff"), glm::cos(glm::radians(temp->cutoff)));
                glUniform1f(glGetUniformLocation(shader, "spotLight.outerCutOff"),glm::cos(glm::radians(temp->outerCutOff)));
            }
            else if(temp->pointLight){
                std::string Lightpos="pointLights["+std::to_string(num_light)+"]";
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".position").c_str()),1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".ambient").c_str()),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".diffuse").c_str()),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".specular").c_str()),1, &(temp->specular*(temp->lightcolor))[0]);
                
                glUniform1f(glGetUniformLocation(shader, (Lightpos+".constant").c_str()),temp->constant);
                glUniform1f(glGetUniformLocation(shader, (Lightpos+".linear").c_str()),temp->linear);
                glUniform1f(glGetUniformLocation(shader, (Lightpos+".quadratic").c_str()),temp->quadratic);
                num_light++;
            }else{
                glUniform3fv(glGetUniformLocation(shader, "dirLight.direction"),1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.ambient"),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.diffuse"),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.specular"),1, &(temp->specular*(temp->lightcolor))[0]);
            }
        }
        glUniform1i(glGetUniformLocation(shader, "NUM_LIGHTS"),num_light);
    }
    else{
        int num_light=0;
        for(int i=0;i<lights_for_BCD.size();i++){
            Light* temp=lights_for_BCD[i];
            if(temp->spotLight){
                glUniform3fv(glGetUniformLocation(shader, "spotLight.position"),1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.direction"),1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.ambient"),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.diffuse"),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "spotLight.specular"),1, &(temp->specular*(temp->lightcolor))[0]);

                glUniform1f(glGetUniformLocation(shader, "spotLight.constant"),temp->constant);
                glUniform1f(glGetUniformLocation(shader, "spotLight.linear"),temp->linear);
                glUniform1f(glGetUniformLocation(shader, "spotLight.quadratic"),temp->quadratic);
                glUniform1f(glGetUniformLocation(shader, "spotLight.cutOff"), glm::cos(glm::radians(temp->cutoff)));
                glUniform1f(glGetUniformLocation(shader, "spotLight.outerCutOff"),glm::cos(glm::radians(temp->outerCutOff)));
            }
            else if(temp->pointLight){
                std::string Lightpos="pointLights["+std::to_string(num_light)+"]";
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".position").c_str()),1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".ambient").c_str()),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".diffuse").c_str()),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".specular").c_str()),1, &(temp->specular*(temp->lightcolor))[0]);
                
                glUniform1f(glGetUniformLocation(shader, (Lightpos+".constant").c_str()),temp->constant);
                glUniform1f(glGetUniformLocation(shader, (Lightpos+".linear").c_str()),temp->linear);
                glUniform1f(glGetUniformLocation(shader, (Lightpos+".quadratic").c_str()),temp->quadratic);
                num_light++;
            }else{
                glUniform3fv(glGetUniformLocation(shader, "dirLight.direction"),1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.ambient"),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.diffuse"),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLightspecular"),1, &(temp->specular*(temp->lightcolor))[0]);
            }
        }
        glUniform1i(glGetUniformLocation(shader, "NUM_LIGHTS"),num_light);
    }
}