#pragma once
#include <vector>
#include <string>

#include "core.h"
#include "Cube.h"

class DOF{
    private:
        glm::vec3 data; 
        glm::vec3 min;
        glm::vec3 max;

    public:
        DOF();
        ~DOF();

        void SetValue(glm::vec3 newdata);
        glm::vec3 GetValue();
        void SetValueSp(float data,int idx);
        void SetXMinMax(float min, float max);
        void SetYMinMax(float min, float max);
        void SetZMinMax(float min, float max);
};