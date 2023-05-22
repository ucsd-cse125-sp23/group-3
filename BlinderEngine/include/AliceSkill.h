#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include "Particles.h"

class AliceSkill {
public:
    struct Particle* leading1;
    struct Particle* leading2;
    struct Particle* leading3;
    struct Particle* leading4;
    bool start;
    bool end;
    Particles* system1;
    Particles* system2;
    Particles* system3;
    Particles* system4;


    void SetUp(glm::mat4 model);
    AliceSkill();
};