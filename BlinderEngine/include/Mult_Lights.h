#pragma once

#include "Light.h"
#include "Camera.h"
#include "DynamicShader.h"
#include "StaticShader.h"
#include <vector>

class Mult_Lights {
private:
    std::vector<Light*> lights_for_BCD;
    std::vector<Light*> lights_for_A;
    bool Alice;
    std::vector<double> timeout_alice;
    std::vector<glm::vec3> spot_center;
    std::vector<glm::vec3> BCD_color_array;

public:
    Mult_Lights(bool _player0);
    ~Mult_Lights();

    //void update(Camera& cam);
    std::vector<Light*> particles_light;
    std::vector<Light*> skill_light;
    void loadToDShader(DynamicShader& shader,Camera& cam);
    void loadToSShader(StaticShader& shader,Camera& cam);
    void loadToUShader(GLuint shader,Camera& cam);
    void updateLightAlice(glm::vec3 lightcenter,bool onmove);
    void AddLightBCD(std::vector<glm::vec3> lightcenters);
    void updateLightAliceV2(glm::mat4 model);
    void updateSkillLight(glm::mat4 model);
    void EmptyAllLights(bool win);
}; 
