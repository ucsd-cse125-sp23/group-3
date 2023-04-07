#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "core.h"
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"
#include "Keyframe.h"
#include "Channel.h"


class Animation {
    private:
        std::vector<Channel*> channels;
        float timestart;
        float timeend;
        int numchan;
        std::vector<Joint*> jntlist;

    public:
        Animation();
        ~Animation();
        void load(const char* file);
        void update(float t);
};