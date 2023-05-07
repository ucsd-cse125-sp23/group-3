#pragma once

#include "Light.h"
#include "Camera.h"
//#include "DynamicShader.h"
//#include "StaticShader.h"
#include <vector>

class Mult_Lights {
    private:
        std::vector<Light*> lights_for_BCD;
        std::vector<Light*> lights_for_A;
        bool Alice;

    public:
        Mult_Lights(bool _player0);
        ~Mult_Lights();

        //void update(Camera& cam);

        //void loadToDShader(DynamicShader& shader,Camera& cam);
        //void loadToSShader(StaticShader& shader,Camera& cam);
        void loadToUShader(GLuint shader,Camera& cam);
}; 