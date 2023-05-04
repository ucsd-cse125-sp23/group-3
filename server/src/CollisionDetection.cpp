#include "CollisionDetection.h"
#include "MapConstants.h"
#include <iostream>
#include <math.h>


int crossingTiles(float x_1, float y_1, float x_2, float y_2) {
    int x_1int = (int)x_1;
    int y_1int = (int)y_1;
    int x_2int = (int)x_2;
    int y_2int = (int)y_2;
    if (x_1 < 0) {
        x_1int -= 1;
    }
    if (y_1 < 0) {
        y_1int -= 1;
    }
    if (x_2 < 0) {
        x_2int -= 1;
    }
    if (y_2 < 0) {
        y_2int -= 1;
    }
    std::vector<bool> result = std::vector<bool>(false, 4);
    if (x_1int == x_2int && y_1int == y_2int) {
        return 0;
    }
    else if (x_1int == x_2int) {
        return 1;
    }
    else if (y_1int == y_2int) {
        return 2;
    }
    float x_dif = x_2 - x_1;
    float y_dif = y_1 - y_2;

    float x_proj = x_2int - x_1;
    float expect_y_proj = x_proj / x_dif * y_dif;
    float y_off = y_1 - expect_y_proj;

    if (fabs((double)(y_off - y_1int)) < BOUNDARY_CHECKER) {
        return 0;
    }
    else if (y_off <= y_1int) {
        return 3;
    }
    else {
        return 4;
    }

}
bool checkerLogic(int mapID, std::vector<std::pair<float, float>> points) {
    if (mapID == 0 || mapID == 2) { // animal

        int type01 = crossingTiles(points[0].first, points[0].second, points[1].first, points[1].second);
        if (type01 == 1) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[1].first)][(int)(points[1].second)];
            if (tile == 3 || tile == 2) {
                std::cerr << "colliding left wall on point 0&1!" << std::endl;
                return true;
            }
        }

        int type23 = crossingTiles(points[2].first, points[2].second, points[3].first, points[3].second);
        if (type23 == 1) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile == 3 || tile == 2) {
                std::cerr << "colliding left wall on point 2&3!" << std::endl;
                return true;
            }
        }

        int type02 = crossingTiles(points[0].first, points[0].second, points[2].first, points[2].second);
        //std::cout<<"type02: "<< type02 <<std::endl;
        if (type02 == 2) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[2].second)];
            if (tile == 3 || tile == 1) {
                std::cerr << "colliding top wall on point 0&2!" << std::endl;
                return true;
            }
        }
        else if (type02 == 3) {
            //std::cout<<"type02: "<< type02 <<std::endl;
            int tile1 = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[2].second)];
            if (tile1 == 3 || tile1 == 1) {
                std::cerr << "colliding type3 top wall on point 0&2!" << std::endl;
                return true;
            }
            int tile2 = MAP_ENCODING[mapID][(int)(points[0].first)][(int)(points[0].second)];
            if (tile2 == 3 || tile2 == 2) {
                std::cerr << "colliding type3 left wall on point 0&2!" << std::endl;
                return true;
            }
        }
        else if (type02 == 4) {
            int tile1 = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[0].second)];
            if (tile1 == 3 || tile1 == 1 || tile1 == 2) {
                std::cerr << "colliding type4 walls on point 0&2!" << std::endl;
                return true;
            }
        }
        int type13 = crossingTiles(points[1].first, points[1].second, points[3].first, points[3].second);
        if (type13 == 2) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile == 3 || tile == 1) {
                std::cerr << "colliding top wall on point 1&3!" << std::endl;
                return true;
            }
        }
        else if (type13 == 3) {
            int tile1 = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile1 == 3 || tile1 == 1) {
                std::cerr << "colliding type3 top wall on point 1&3!" << std::endl;
                return true;
            }
            int tile2 = MAP_ENCODING[mapID][(int)(points[1].first)][(int)(points[1].second)];
            if (tile2 == 3 || tile2 == 2) {
                std::cerr << "colliding type3 left wall on point 1&3!" << std::endl;
                return true;
            }
        }
        else if (type13 == 4) {
            int tile1 = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[1].second)];
            if (tile1 == 3 || tile1 == 1 || tile1 == 2) {
                std::cerr << "colliding type4 walls on point 1&3!" << std::endl;
                return true;
            }
        }
    }
    else if (mapID == 1) {

        int type01 = crossingTiles(points[0].first, points[0].second, points[1].first, points[1].second);
        //std::cout<<"type01: " << type01<<std::endl;
        if (type01 == 1) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[1].first)][(int)(points[1].second)];
            if (tile == 3 || tile == 2) {
                std::cerr << "colliding left wall on point 0&1!" << std::endl;
                return true;
            }
        }

        int type23 = crossingTiles(points[2].first, points[2].second, points[3].first, points[3].second);
        if (type23 == 1) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile == 3 || tile == 2) {
                std::cerr << "colliding left wall on point 2&3!" << std::endl;
                return true;
            }
        }

        int type02 = crossingTiles(points[0].first, points[0].second, points[2].first, points[2].second);

        if (points[0].first < 0) {
            std::cerr << "type02: " << type02 << std::endl;
        }

        if (type02 == 2) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[2].second)];
            if (tile == 3 || tile == 1) {
                std::cerr << "colliding top wall on point 0&2!" << std::endl;
                return true;
            }
        }
        else if (type02 == 3) {
            //std::cout<<"type02: "<< type02 <<std::endl;
            int tile1 = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[0].second)];
            if (tile1 == 3 || tile1 == 1) {
                std::cerr << "colliding type3 top wall on point 0&2!" << std::endl;
                return true;
            }
            int tile2 = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[2].second)];
            if (tile2 == 3 || tile2 == 2) {
                std::cerr << "colliding type3 left wall on point 0&2!" << std::endl;
                return true;
            }
        }
        else if (type02 == 4) {
            int tile1 = MAP_ENCODING[mapID][(int)(points[2].first)][(int)(points[2].second)];
            if (tile1 == 3 || tile1 == 1) {
                std::cerr << "colliding type4 top wall on point 0&2!" << std::endl;
                return true;
            }
            int tile2 = MAP_ENCODING[mapID][(int)(points[0].first)][(int)(points[2].second)];
            if (tile2 == 3 || tile2 == 2) {
                std::cerr << "colliding type4 left wall on point 0&2!" << std::endl;
                return true;
            }
        }

        int type13 = crossingTiles(points[1].first, points[1].second, points[3].first, points[3].second);
        if (type13 == 2) {
            //top left wall on point 0&1
            int tile = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile == 3 || tile == 1) {
                std::cerr << "colliding top wall on point 1&3!" << std::endl;
                return true;
            }
        }
        else if (type13 == 3) {
            int tile1 = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[1].second)];
            if (tile1 == 3 || tile1 == 1) {
                std::cerr << "colliding type3 top wall on point 1&3!" << std::endl;
                return true;
            }
            int tile2 = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile2 == 3 || tile2 == 2) {
                std::cerr << "colliding type3 left wall on point 1&3!" << std::endl;
                return true;
            }
        }
        else if (type13 == 4) {
            int tile1 = MAP_ENCODING[mapID][(int)(points[3].first)][(int)(points[3].second)];
            if (tile1 == 3 || tile1 == 1) {
                std::cerr << "colliding type4 top wall on point 1&3!" << std::endl;
                return true;
            }
            int tile2 = MAP_ENCODING[mapID][(int)(points[1].first)][(int)(points[3].second)];
            if (tile2 == 3 || tile2 == 2) {
                std::cerr << "colliding type4 left wall on point 1&3!" << std::endl;
                return true;
            }
        }
    }
    return false;
}
int largerTileIndex(float p1, float p2) {
    if ((int)p1 > (int)p2)
        return (int)p1;
    return (int)p2;
}

CollisionDetection::CollisionDetection() {}

CollisionDetection::~CollisionDetection() {}

void CollisionDetection::checkCollision() {

}

bool CollisionDetection::checkCollisionWithWall(int mapID, std::vector<std::pair<float, float>> points_org) {
    // inside submap - 4 points
    std::vector<std::pair<float, float>> points = std::vector<std::pair<float, float>>();
    if (points_org.size() == 4) {
        for (int i = 0; i < points_org.size(); i++) {
            points.push_back(points_org.at(i));
        }
        return checkerLogic(mapID, points);
    }
    else {
        bool returnlogic;
        for (int i = 0; i < 4; i++) {
            points.push_back(points_org.at(i));
        }
        if (mapID == 0 && points.at(0).first > 4.0f) {
            returnlogic = checkerLogic(1, points);
            if (returnlogic) {
                std::cerr << "8 points map1 collision on edge 2" << std::endl;
                return true;
            }
            for (int i = 0; i < 4; i++) {
                points.at(i) = points_org.at(i + 4);
            }
            if (returnlogic) {
                std::cerr << "8 points map1 collision on edge 2" << std::endl;
                return true;
            }
            return checkerLogic(0, points);
        }
        else if (mapID == 0) {
            returnlogic = checkerLogic(0, points);
            if (returnlogic) {
                std::cerr << "8 points map0 collision on edge 3" << std::endl;
                return true;
            }
            for (int i = 0; i < 4; i++) {
                points.at(i) = points_org.at(i + 4);
            }
            return checkerLogic(2, points);
        }
        else if (mapID == 1) {
            returnlogic = checkerLogic(1, points);
            if (returnlogic) {
                std::cerr << "8 points map1 collision on edge 1" << std::endl;
                return true;
            }
            for (int i = 0; i < 4; i++) {
                points.at(i) = points_org.at(i + 4);
            }
            return checkerLogic(0, points);
        }
        else {
            returnlogic = checkerLogic(0, points);
            if (returnlogic) {
                std::cerr << "8 points map0 collision on edge 4" << std::endl;
                return true;
            }
            for (int i = 0; i < 4; i++) {
                points.at(i) = points_org.at(i + 4);
            }
            return checkerLogic(2, points);
        }
        std::cerr << "Unhandeled?" << std::endl;

    }
    return false;

}

bool CollisionDetection::collideWithObstacle(glm::mat4& player, std::vector<ObsObjectSv*>& obs_vec) // AABB - Circle collision
{
    // get center point circle first 
    float* pSource = (float*)glm::value_ptr(player);
    glm::vec2 center(pSource[12], pSource[14]);
    // std::cout << "player position " << center.x << " " << center.y << std::endl;

    
    for (ObsObjectSv* obs : obs_vec) {
        // calculate AABB info (center, half-extents)
        float* pSourceObs = (float*)glm::value_ptr(obs->pSrc);
        glm::vec2 centerObs(pSourceObs[12], pSourceObs[14]);
        // std::cout << "obs position " << centerObs.x << " " << centerObs.y << std::endl;
        glm::vec2 aabb_half_extents(obs->width / 2.0f, obs->height / 2.0f);
        //glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
        // get difference vector between both centers
        glm::vec2 difference = center - centerObs;
        glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
        // now that we know the clamped values, add this to AABB_center and we get the value of box closest to circle
        glm::vec2 closest = centerObs + clamped;
        // now retrieve vector between center circle and closest point AABB and check if length < radius
        difference = closest - center;
        // std::cout << "diff " << difference.x << "" << difference.y << std::endl;
        // TODO: change player radius
        if (glm::length(difference) < PLAYER_RADIUS) { // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
            // std::cout << "colliding with obstacle" << std::endl;
            return true;
        }
    }
 

    return false;
}

std::vector<bool> CollisionDetection::collideBetweenCircles(std::vector<glm::mat4> players) {
    std::vector<glm::vec2> playersXY;
    std::vector<bool> colliding({false, false, false, false});

    for (glm::mat4 p : players) {
        float* pSource = (float*)glm::value_ptr(p);
        glm::vec2 pXY(pSource[12], pSource[14]);
        playersXY.push_back(pXY);
    }


    for (int i = 0; i < playersXY.size(); i++) {
        for (int j = i + 1; j < playersXY.size(); j++) {
            if (glm::length(playersXY[i] - playersXY[j]) < PLAYER_RADIUS * 2) {
                colliding[i] = true;
                colliding[j] = true;
            }
        }
    }
    return colliding;
}