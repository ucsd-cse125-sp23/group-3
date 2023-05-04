#pragma once

#include <vector>
#include <utility>
#include "core.h"
#include "DynamicShader.h"
#include "StaticShader.h"

class Light {
    private:

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        bool spotLight;
        float constant;
        float linear;
        float quadartic;

    public:
        Light(glm::vec3 _position, glm::vec3 _direction, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, bool spotlight);
        ~Light();

        void SetLighttoDShader(DynamicShader shader);
        void SetLighttoSShader(StaticShader shader);
};