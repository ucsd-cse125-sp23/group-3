#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include "Particles.h"
#include "Light.h"
#include <vector>
#include "StaticShader.h"

class AliceSkill {
public:
    std::vector<struct Particle* > leadingparticles;
    bool start;
    bool setup;
    glm::vec3 dest;
    std::vector<Particles*> systems;
    std::vector<Light*> particles_light;
    std::vector<glm::vec3> initial_pos;
    int light_index_start, light_index_end;



    AliceSkill(std::vector<Light*>& light);
    void SetUp(glm::mat4 model);
    void update(float dt);
    void draw(StaticShader shader, const glm::mat4& viewProjMtx);

};