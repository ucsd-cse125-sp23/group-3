#pragma once
#include <core.h>
#include <StaticShader.h>

class Skybox {
public:
    Skybox();
    void draw(const glm::mat4& projection, const glm::mat4& view, StaticShader& shader);
private:
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int skyboxTextureID;
};