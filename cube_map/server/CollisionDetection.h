#pragma once

#include <vector>

#include "core.h"

class CollisionDetection {
    private:

    public:
        CollisionDetection();
        ~CollisionDetection();

        void checkCollision();
        /**
         * Checks if a character is colliding with wall
         * 
         * @param mapID, x, y - submap id and character 2d position on the map; 
         * can be obtained by calling Map::getPosition
        */
        bool checkCollisionWithWall(int mapID, std::vector<std::pair<float, float>> points);
};