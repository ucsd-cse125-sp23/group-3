#pragma once
#include <vector>
#include <string>
#include "core.h"
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"
#include <iostream>

class Keyframe {
    private:

        float Time;
        float Value;
        float TangentIn,TangentOut;
        int RuleIn,RuleOut; 

        glm::vec4 coeffs;
        Keyframe* lastframe;
        Keyframe* nextframe;

    public:
        Keyframe(float time, float value,int rulein,int ruleout,float tanin,float tanout);
        ~Keyframe();

        void computeTangents();
        void computeCoeffcients();
        void setNext(Keyframe* nextFrame);
        void setLast(Keyframe* lastFrame);

        float getTime();
        float getValue();
        float getTanIn();
        float getTanOut();
        glm::vec4 getCoef();

};