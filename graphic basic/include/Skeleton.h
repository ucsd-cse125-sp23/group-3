#pragma once

#include <vector>
#include <string>

#include "core.h"
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"

class Skeleton {
    private:
        Joint* root;

    public:
        Skeleton();
        ~Skeleton();
        
        bool Load(const char *file);
        void Update();
        void Draw(const glm::mat4& viewProjMtx, GLuint shader);
        Joint* find(int num);
};