#pragma once

#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "core.h"
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"
#include "Keyframe.h"

class Channel{
    private:
        int numKeyframes;
        int extrapolateIn, extrapolateOut;
        std::vector<Keyframe*> keyframes;
        float interpolate(float t);
        
    public:
        Channel(int numKeyframes,int extrapolateIn, int extrapolateOut);
        ~Channel();

        void addFrame(Keyframe* data);
        void load();
        float eval(float t);
};