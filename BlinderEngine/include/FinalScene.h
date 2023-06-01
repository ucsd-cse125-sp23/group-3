#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include <vector>
#include "StaticShader.h"
#include "DynamicShader.h"

class FinalScene {
public:
    bool status;
    FinalScene(bool win);
    void update(float dt);
    void draw(StaticShader Sshader, DynamicShader Dshader,const glm::mat4& viewProjMtx);

};