#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"
#include <vector>
#include "StaticShader.h"
#include "DynamicShader.h"
#include "ObjObject.h"
#include "DaeObject.h"
#include "graphic2D.h"

class FinalScene {
public:
    bool status;
    std::shared_ptr<ObjObject> backWallwin;
    std::shared_ptr<ObjObject> backWalllose;
    std::shared_ptr<ObjObject> ground;
    std::vector<std::shared_ptr<DaeObject>> players;
    std::vector<float> playertime;
    std::vector<bool> playerAnim;
    graphic2D* winpage;
    graphic2D* winpage_enter;
    graphic2D* losepage;
    graphic2D* losepage_enter;

    FinalScene(bool win, std::vector<std::shared_ptr<DaeObject>> players);
    void update(float dt);
    void draw(StaticShader Sshader, DynamicShader Dshader, StaticShader Ushader, const glm::mat4& projection, const glm::mat4& view);

    float tot_dt = 0;
};