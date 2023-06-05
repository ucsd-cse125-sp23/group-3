#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include <vector>
#include "StaticShader.h"
#include "DynamicShader.h"
#include "ObjObject.h"
#include "DaeObject.h"

class FinalScene {
public:
    bool status;
    std::shared_ptr<ObjObject> backWallwin;
    std::shared_ptr<ObjObject> backWalllose;
    std::shared_ptr<ObjObject> ground;
    std::vector<std::shared_ptr<DaeObject>> players;
    std::vector<float> playertime;
    std::vector<bool> playerAnim;

    FinalScene(bool win,std::vector<std::shared_ptr<DaeObject>> players);
    void update(float dt);
    void draw(StaticShader Sshader, DynamicShader Dshader,const glm::mat4& projection, const glm::mat4& view);

};