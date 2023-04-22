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
        /**
         * Checks if a character is colliding with wall
         * 
         * @param x, y - character 2d position on the map; can be obtained from 
         * Map::getPosition (check IdleCallback() in Window.cpp)
        */
        void checkCollisionWithWall(float x, float y);
};