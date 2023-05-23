#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include "Particles.h"
#include "Light.h"
#include <vector>

class AliceSkill{
    public:
        std::vector<struct Particle* > leadingparticles;
        bool start;
        bool setup;
        std::vector<Particles*> systems;
        std::vector<Light*> particles_light;
        int light_index_start,light_index_end;
        

        
        AliceSkill(std::vector<Light*> &light);
        void SetUp(glm::mat4 model);
        void update(float dt);
        void draw(Shader shader,const glm::mat4& viewProjMtx,glm::mat4 camView);

};