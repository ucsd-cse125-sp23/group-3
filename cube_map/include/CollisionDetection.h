#pragma once

#include <vector>

#include "core.h"
#include "Cube.h"
#include "Submap.h"

class CollisionDetection {
    private:

    public:
        CollisionDetection();
        ~CollisionDetection();

        void checkCollision();
        void checkCollisionWithWall(float x, float y); // x, y as in Window.cpp IdleCallback()s
};