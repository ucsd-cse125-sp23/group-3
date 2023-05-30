#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include "Particles.h"
#include "Light.h"
#include <vector>
#include "StaticShader.h"

class DaveSkill {
public:
    std::vector<struct Particle* > leadingparticles;
    bool start;
    bool setup;
    std::vector<Particles*> systems;
    std::vector<Light*> particles_light;
    std::vector<glm::vec3> initial_pos;
    int light_index_start, light_index_end;
    float angle;
    float radius;
    float ending_height;
    float height;
    glm::mat4 _model;

    DaveSkill(std::vector<Light*>& light);
    void SetUp(glm::mat4 model);
    void update(float dt, glm::mat4 model);
    void draw(StaticShader shader, const glm::mat4& viewProjMtx);

};