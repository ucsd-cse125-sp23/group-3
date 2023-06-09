#include "Mult_Lights.h"
#include <string>
#include <cstring>
#include <glm/gtx/string_cast.hpp>

double time_out_val = 3.5;
/*
 Light class::
 bool _spotLight,
 bool _pointLight,
 glm::vec3 _color,
 glm::vec3 _direction,
 glm::vec3 _position,
 float _ambient,
 float _diffuse,
 float _specular
*/
Mult_Lights::Mult_Lights(bool _player0) {
    Light* adirLight = new Light(false, false, glm::vec3(0.2f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), 0.15f, 0.0f, 0.0f);
    Light* dirLight = new Light(false, false, glm::vec3(0.2f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), 1.5f, 0.0f, 0.0f);
    lights_for_A.push_back(adirLight);
    lights_for_BCD.push_back(dirLight);
    spot_center = std::vector<glm::vec3>();
    Alice = _player0;
    BCD_color_array = std::vector<glm::vec3>({ glm::vec3(1.0f),glm::vec3(1.0f),glm::vec3(1.0f) });
    particles_light = std::vector<Light*>();
}

Mult_Lights::~Mult_Lights() {

}
bool checkLights(glm::vec3 lightcenter, std::vector<glm::vec3> spotcenters) {
    if (spotcenters.size() == 0) {
        return true;
    }
    for (int i = 0; i < spotcenters.size(); i++) {
        if (glm::length(lightcenter - spotcenters[i]) < 0.1) {
            return false;
        }
    }
    return true;
}

void Mult_Lights::AddLightBCD(std::vector<glm::vec3> lightcenters) {
    for (int i = 0; i < lightcenters.size(); i++) {
        glm::vec3 lightpos = glm::vec3(lightcenters[i].x, 20.0f, lightcenters[i].z);
        Light* pointLight1 = new Light(false, true, BCD_color_array[i], glm::vec3(0.0f, -1.0f, 0.0f), lightpos, 0.4f, 1.5f, 0.1f);
        pointLight1->SetParam(1.0f, 0.01f, 0.004f);
        lights_for_BCD.push_back(pointLight1);
    }
}

void Mult_Lights::updateLightAlice(glm::vec3 lightcenter, bool onmove) {
    glm::vec3 lightpos = glm::vec3(lightcenter.x, 30.0f, lightcenter.z);
    if (checkLights(lightpos, spot_center) && onmove) {
        Light* spotLight = new Light(true, false, glm::vec3(1.0f), glm::vec3(0.0f, -1.0f, 0.0f), lightpos, 0.3f, 2.8f, 0.2f);
        //spotLight->SetParam(1.0f,0.6f,0.1f);
        spotLight->SetParam(1.0f, 0.07f, 0.03f);
        spotLight->SetSpot(40.0f, 100.0f);
        spot_center.push_back(lightpos);
        lights_for_A.push_back(spotLight);
        timeout_alice.push_back(glfwGetTime());
    }
    int skip_checker = -1;
    if (onmove) {
        for (int i = 0; i < spot_center.size(); i++) {
            if (glm::length(lightpos - spot_center[i]) < 0.1) {
                timeout_alice[i] = glfwGetTime();
                skip_checker = i;
            }
        }
    }
    double newtime = glfwGetTime();
    for (int i = 0; i < spot_center.size(); i++) {
        if (skip_checker == i) {
            lights_for_A[i + 1]->lightcolor = glm::vec3(1.0f);
            //std::cout<<skip_checker<<std::endl;
            continue;
        }
        double diff = newtime - timeout_alice[i];
        if (diff > time_out_val) {
            lights_for_A.erase(lights_for_A.begin() + i + 1);
            timeout_alice.erase(timeout_alice.begin() + i);
            spot_center.erase(spot_center.begin() + i);
        }
        /*else if(diff<time_out_val*0.2){
            float scale= diff/(time_out_val*0.2)+1;
            lights_for_A[i]->lightcolor=glm::vec3(0.5f)*scale;
        }*/
        else if (diff > time_out_val * 0.7) {
            float scale = (time_out_val - diff) / (time_out_val * 0.3);
            //std::cout<<scale<<std::endl;
            lights_for_A[i + 1]->lightcolor = glm::vec3(1.0f) * scale;
            //std::cout<<scale<<std::endl;
        }
        else {
            lights_for_A[i + 1]->lightcolor = glm::vec3(1.0f);
        }

    }
}

void Mult_Lights::EmptyAllLights(bool win) {
    lights_for_A.clear();
    lights_for_BCD.clear();
    skill_light.clear();
    particles_light.clear();
    Light* endLight1=new Light(true, false, glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(-0.9f, -1.0f, -1.0f), glm::vec3(20.0f, 20.0f, 18.0f), 1.5f, 2.0f, 0.1f);
    endLight1->SetParam(1.0f, 0.01f, 0.004f);
    endLight1->SetSpot(5.0f, 30.0f);
    Light* endLight2 = new Light(true, false, glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.9f, -1.0f, -1.0f), glm::vec3(-20.0f, 20.0f, 18.0f), 1.5f, 2.0f, 0.1f);
    endLight2->SetParam(1.0f, 0.01f, 0.004f);
    endLight2->SetSpot(5.0f, 30.0f);
    if (win) {
        lights_for_A.push_back(endLight1);
        lights_for_A.push_back(endLight2);
        lights_for_BCD.push_back(endLight1);
        lights_for_BCD.push_back(endLight2);
        return;
    }
    endLight1 = new Light(true, false, glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(-0.9f, -1.0f, -1.0f), glm::vec3(20.0f, 20.0f, 18.0f), 1.5f, 2.0f, 0.1f);
    endLight1->SetParam(1.0f, 0.01f, 0.004f);
    endLight1->SetSpot(5.0f, 30.0f);
    endLight2 = new Light(true, false, glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.9f, -1.0f, -1.0f), glm::vec3(-20.0f, 20.0f, 18.0f), 1.5f, 2.0f, 0.1f);
    endLight2->SetParam(1.0f, 0.01f, 0.004f);
    endLight2->SetSpot(5.0f, 30.0f);
    lights_for_A.push_back(endLight1);
    lights_for_A.push_back(endLight2);
    lights_for_BCD.push_back(endLight1);
    lights_for_BCD.push_back(endLight2);
}

void Mult_Lights::updateLightAliceV2(glm::mat4 model) {

    float* pSource = (float*)glm::value_ptr(model);
    glm::vec3 lightpos = glm::vec3(pSource[12], 5.0f, pSource[14]);
    Light* spotLight = new Light(true, false, glm::vec3(1.0f), glm::vec3(0.0f, -1.0f, 0.0f), lightpos, 0.3f, 2.8f, 0.2f);
    spotLight->SetParam(1.0f, 0.3f, 0.1f);
    spotLight->SetSpot(40.0f, 80.0f);
    if (lights_for_A.size() == 1) {
        lights_for_A.push_back(spotLight);
    }
    else {
        lights_for_A[1] = spotLight;
    }

}


void Mult_Lights::loadToDShader(DynamicShader& shader,Camera& cam){
    shader.use();
    shader.setVec3("viewPos", cam.CameraPos);

    std::vector<Light*> sub_lights;
    for (auto l : particles_light) sub_lights.push_back(l);
    for (auto l : skill_light) sub_lights.push_back(l);
    if(Alice){
        int num_light_point=0;
        int num_light_spot = 0;
        for (auto l : lights_for_A) sub_lights.push_back(l);
        /*for (int i = 0; i<lights_for_A.size() + particles_light.size(); i++) {
            Light* temp;
            if (i < lights_for_A.size()) {
                 temp= lights_for_A[i];
            }
            else {
                temp = particles_light[i - lights_for_A.size()];
            }

           */
        for(auto temp : sub_lights){
            if(temp->spotLight){
                std::string Lightpos = "spotLight[" + std::to_string(num_light_spot) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".direction").c_str(), temp->direction);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient*(temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse*(temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular*(temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                shader.setFloat((Lightpos + ".cutOff").c_str(), glm::cos(glm::radians(temp->cutoff)));
                shader.setFloat((Lightpos + ".outerCutOff").c_str(), glm::cos(glm::radians(temp->outerCutOff)));
                num_light_spot++;
            }
            else if(temp->pointLight){
                std::string Lightpos="pointLights["+std::to_string(num_light_point)+"]";
                shader.setVec3((Lightpos+".position").c_str(), temp->position);
                shader.setVec3((Lightpos+".ambient").c_str(), temp->ambient*(temp->lightcolor));
                shader.setVec3((Lightpos+".diffuse").c_str(), temp->diffuse*(temp->lightcolor));
                shader.setVec3((Lightpos+".specular").c_str(), temp->specular*(temp->lightcolor));
                shader.setFloat((Lightpos+".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos+".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos+".quadratic").c_str(), temp->quadratic);
                num_light_point++;
            }else{
                shader.setVec3("dirLight.direction", temp->direction);
                shader.setVec3("dirLight.ambient", temp->ambient*(temp->lightcolor));
                shader.setVec3("dirLight.diffuse", temp->diffuse*(temp->lightcolor));
                shader.setVec3("dirLight.specular", temp->specular*(temp->lightcolor));
            }
        }
        shader.setInt("NUM_LIGHTS_POINT",num_light_point);
        shader.setInt("NUM_LIGHTS_SPOT", num_light_spot);
    }
    else{
        int num_light_point = 0;
        int num_light_spot = 0;

        for (auto l : lights_for_BCD) sub_lights.push_back(l);
        /*
        for(int i=0;i<lights_for_BCD.size() + particles_light.size();i++){
            Light* temp;
            if (i < lights_for_BCD.size()) {
                temp = lights_for_BCD[i];
            }
            else {
                temp = particles_light[i - lights_for_BCD.size()];
            }
        */
        for(auto temp : sub_lights){
            if (temp->spotLight) {
                std::string Lightpos = "spotLight[" + std::to_string(num_light_spot) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".direction").c_str(), temp->direction);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient * (temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse * (temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular * (temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                shader.setFloat((Lightpos + ".cutOff").c_str(), glm::cos(glm::radians(temp->cutoff)));
                shader.setFloat((Lightpos + ".outerCutOff").c_str(), glm::cos(glm::radians(temp->outerCutOff)));
                num_light_spot++;
            }
            else if (temp->pointLight) {
                std::string Lightpos = "pointLights[" + std::to_string(num_light_point) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient * (temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse * (temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular * (temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                num_light_point++;
            }
            else {
                shader.setVec3("dirLight.direction", temp->direction);
                shader.setVec3("dirLight.ambient", temp->ambient * (temp->lightcolor));
                shader.setVec3("dirLight.diffuse", temp->diffuse * (temp->lightcolor));
                const glm::vec3 color = (temp->specular) * (temp->lightcolor);
                shader.setVec3("dirLight.specular", color);
                //std::cout << glm::to_string(color)<<std::endl;
            }
        }
        shader.setInt("NUM_LIGHTS_POINT", num_light_point);
        shader.setInt("NUM_LIGHTS_SPOT", num_light_spot);
    }
}

void Mult_Lights::loadToSShader(StaticShader& shader, Camera& cam) {
    shader.use();
    shader.setVec3("viewPos", cam.CameraPos);

    std::vector<Light*> sub_lights;
    for (auto l : particles_light) sub_lights.push_back(l);
    for (auto l : skill_light) sub_lights.push_back(l);
    if (Alice) {
        int num_light_point = 0;
        int num_light_spot = 0;

        for (auto l : lights_for_A) sub_lights.push_back(l);

        /*
        for (int i = 0; i < lights_for_A.size() + particles_light.size(); i++) {
            Light* temp;
            if (i < lights_for_A.size()) {
                temp = lights_for_A[i];
            }
            else {
                temp = particles_light[i - lights_for_A.size()];
            }*/
        for (auto temp : sub_lights){
            if (temp->spotLight) {
                std::string Lightpos = "spotLight[" + std::to_string(num_light_spot) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".direction").c_str(), temp->direction);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient * (temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse * (temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular * (temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                shader.setFloat((Lightpos + ".cutOff").c_str(), glm::cos(glm::radians(temp->cutoff)));
                shader.setFloat((Lightpos + ".outerCutOff").c_str(), glm::cos(glm::radians(temp->outerCutOff)));
                num_light_spot++;
            }
            else if (temp->pointLight) {
                std::string Lightpos = "pointLights[" + std::to_string(num_light_point) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient * (temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse * (temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular * (temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                num_light_point++;
            }
            else {
                shader.setVec3("dirLight.direction", temp->direction);
                shader.setVec3("dirLight.ambient", temp->ambient * (temp->lightcolor));
                shader.setVec3("dirLight.diffuse", temp->diffuse * (temp->lightcolor));
                shader.setVec3("dirLight.specular", temp->specular * (temp->lightcolor));
            }
        }
        shader.setInt("NUM_LIGHTS_POINT", num_light_point);
        shader.setInt("NUM_LIGHTS_SPOT", num_light_spot);
    }
    else {
        int num_light_point = 0;
        int num_light_spot = 0;

        for (auto l : lights_for_BCD) sub_lights.push_back(l);
        /*for (int i = 0; i < lights_for_BCD.size() + particles_light.size(); i++) {
            Light* temp;
            if (i < lights_for_BCD.size()) {
                temp = lights_for_BCD[i];
            }
            else {
                temp = particles_light[i - lights_for_BCD.size()];
            }*/
        for (auto temp : sub_lights){
            if (temp->spotLight) {
                std::string Lightpos = "spotLight[" + std::to_string(num_light_spot) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".direction").c_str(), temp->direction);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient * (temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse * (temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular * (temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                shader.setFloat((Lightpos + ".cutOff").c_str(), glm::cos(glm::radians(temp->cutoff)));
                shader.setFloat((Lightpos + ".outerCutOff").c_str(), glm::cos(glm::radians(temp->outerCutOff)));
                num_light_spot++;
            }
            else if (temp->pointLight) {
                std::string Lightpos = "pointLights[" + std::to_string(num_light_point) + "]";
                shader.setVec3((Lightpos + ".position").c_str(), temp->position);
                shader.setVec3((Lightpos + ".ambient").c_str(), temp->ambient * (temp->lightcolor));
                shader.setVec3((Lightpos + ".diffuse").c_str(), temp->diffuse * (temp->lightcolor));
                shader.setVec3((Lightpos + ".specular").c_str(), temp->specular * (temp->lightcolor));
                shader.setFloat((Lightpos + ".constant").c_str(), temp->constant);
                shader.setFloat((Lightpos + ".linear").c_str(), temp->linear);
                shader.setFloat((Lightpos + ".quadratic").c_str(), temp->quadratic);
                num_light_point++;
            }
            else {
                shader.setVec3("dirLight.direction", temp->direction);
                shader.setVec3("dirLight.ambient", temp->ambient * (temp->lightcolor));
                shader.setVec3("dirLight.diffuse", temp->diffuse * (temp->lightcolor));
                const glm::vec3 color = (temp->specular) * (temp->lightcolor);
                shader.setVec3("dirLight.specular", color);
                //std::cout << glm::to_string(color)<<std::endl;
            }
        }
        shader.setInt("NUM_LIGHTS_POINT", num_light_point);
        shader.setInt("NUM_LIGHTS_SPOT", num_light_spot);
    }
}


void Mult_Lights::loadToUShader(GLuint shader, Camera& cam) {
    glUseProgram(shader);
    glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, &cam.CameraPos[0]);

    std::vector<Light*> sub_lights;
    for (auto l : particles_light) sub_lights.push_back(l);
    for (auto l : skill_light) sub_lights.push_back(l);

    if (Alice) {
        int num_light_point = 0;
        int num_light_spot = 0;

        for (auto l : lights_for_A) sub_lights.push_back(l);
        /*for (int i = 0; i < lights_for_A.size() + particles_light.size(); i++) {
            Light* temp;
            if (i < lights_for_A.size()) {
                temp = lights_for_A[i];
            }
            else {
                temp = particles_light[i - lights_for_A.size()];
            }*/
            //std::cout<<lights_for_A.size()<<std::endl;
        for (auto temp : sub_lights){
            if (temp->spotLight) {
                std::string Lightpos = "spotLight[" + std::to_string(num_light_spot) + "]";
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".position").c_str()), 1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".direction").c_str()), 1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".ambient").c_str()), 1, &(temp->ambient * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".diffuse").c_str()), 1, &(temp->diffuse * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".specular").c_str()), 1, &(temp->specular * (temp->lightcolor))[0]);

                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".constant").c_str()), temp->constant);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".linear").c_str()), temp->linear);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".quadratic").c_str()), temp->quadratic);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".cutOff").c_str()), glm::cos(glm::radians(temp->cutoff)));
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".outerCutOff").c_str()), glm::cos(glm::radians(temp->outerCutOff)));
                num_light_spot++;
            }
            else if (temp->pointLight) {
                std::string Lightpos = "pointLights[" + std::to_string(num_light_point) + "]";
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".position").c_str()), 1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".ambient").c_str()), 1, &(temp->ambient * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".diffuse").c_str()), 1, &(temp->diffuse * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".specular").c_str()), 1, &(temp->specular * (temp->lightcolor))[0]);

                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".constant").c_str()), temp->constant);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".linear").c_str()), temp->linear);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".quadratic").c_str()), temp->quadratic);
                num_light_point++;
            }
            else {
                glUniform3fv(glGetUniformLocation(shader, "dirLight.direction"), 1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.ambient"), 1, &(temp->ambient * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.diffuse"), 1, &(temp->diffuse * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.specular"), 1, &(temp->specular * (temp->lightcolor))[0]);
            }
        }
        glUniform1i(glGetUniformLocation(shader, "NUM_LIGHTS_POINT"), num_light_point);
        glUniform1i(glGetUniformLocation(shader, "NUM_LIGHTS_SPOT"), num_light_spot);
    }
    else{
        int num_light_point=0;
        int num_light_spot=0;

        for (auto l : lights_for_BCD) sub_lights.push_back(l);
        /*for (int i = 0; i<lights_for_BCD.size() + particles_light.size(); i++) {
            Light* temp;
            if (i < lights_for_BCD.size()) {
                temp = lights_for_BCD[i];
            }
            else {
                temp = particles_light[i - lights_for_BCD.size()];
            }*/
        for (auto temp : sub_lights){
            if(temp->spotLight){
                std::string Lightpos="spotLight["+std::to_string(num_light_spot)+"]";
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".position").c_str()),1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".direction").c_str()),1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".ambient").c_str()),1, &(temp->ambient*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".diffuse").c_str()),1, &(temp->diffuse*(temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos+".specular").c_str()),1, &(temp->specular*(temp->lightcolor))[0]);

                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".constant").c_str()), temp->constant);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".linear").c_str()), temp->linear);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".quadratic").c_str()), temp->quadratic);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".cutOff").c_str()), glm::cos(glm::radians(temp->cutoff)));
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".outerCutOff").c_str()), glm::cos(glm::radians(temp->outerCutOff)));
                num_light_spot++;
            }
            else if (temp->pointLight) {
                std::string Lightpos = "pointLights[" + std::to_string(num_light_point) + "]";
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".position").c_str()), 1, &(temp->position)[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".ambient").c_str()), 1, &(temp->ambient * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".diffuse").c_str()), 1, &(temp->diffuse * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, (Lightpos + ".specular").c_str()), 1, &(temp->specular * (temp->lightcolor))[0]);

                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".constant").c_str()), temp->constant);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".linear").c_str()), temp->linear);
                glUniform1f(glGetUniformLocation(shader, (Lightpos + ".quadratic").c_str()), temp->quadratic);
                num_light_point++;
            }
            else {
                glUniform3fv(glGetUniformLocation(shader, "dirLight.direction"), 1, &(temp->direction)[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.ambient"), 1, &(temp->ambient * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLight.diffuse"), 1, &(temp->diffuse * (temp->lightcolor))[0]);
                glUniform3fv(glGetUniformLocation(shader, "dirLightspecular"), 1, &(temp->specular * (temp->lightcolor))[0]);
            }
        }
        glUniform1i(glGetUniformLocation(shader, "NUM_LIGHTS_POINT"), num_light_point);
        glUniform1i(glGetUniformLocation(shader, "NUM_LIGHTS_SPOT"), num_light_spot);
        //std::cout<<num_light_point<<std::endl;
    }
}

void Mult_Lights::updateSkillLight(glm::mat4 model) {
    /*glm::mat4 model = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };*/
    float* pSource = (float*)glm::value_ptr(model);
    glm::vec3 lightpos = glm::vec3(pSource[12], 5.0f, pSource[14]);
    Light* spotLight = new Light(true, false, glm::vec3(1.0f), glm::vec3(0.0f, -1.0f, 0.0f), lightpos, 0.3f, 2.8f, 0.2f);
    spotLight->SetParam(1.0f, 0.3f, 0.1f);
    spotLight->SetSpot(40.0f, 80.0f);
    /*if (skill_light.size() == 1) {
        skill_light[0] = spotLight;
    }
    else {
        skill_light.push_back(spotLight);
    }*/
    skill_light.push_back(spotLight);
}

