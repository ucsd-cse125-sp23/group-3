#pragma once

#include <vector>
#include <utility>
#include "core.h"

class Light {
    public:
        bool spotLight;
        bool pointLight;

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 lightcolor;

        float ambient;
        float diffuse;
        float specular;
        
        float constant;
        float linear;
        float quadratic;

        float cutoff;
        float outerCutOff;

    public:
        Light(bool _spotLight,bool _pointLight,glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, float _ambient, float _diffuse, float _specular);
        ~Light();

        void SetParam(float _constant, float _linear, float _quadratic);
        void SetSpot(float _cutoff,float _outerCutOff);
};