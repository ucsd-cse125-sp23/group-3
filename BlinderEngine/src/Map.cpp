﻿#include <string>
#include <iostream>
#include "Map.h"
#include "MapConstants.h"
#include <glm/gtx/string_cast.hpp>

int MAP_ENCODING[3][6][6] = { 0 };

Map::Map() {
    //objObjectWall = std::make_shared<ObjObject>("./resources/objects/damaged_wall/damaged_wall.fbx", glm::vec3(0.064f, 0.08f, 0.04f));
    objObjectWall = std::make_shared<ObjObject>("./resources/objects/wall/wall3.obj", glm::vec3(0.42f, 0.6f, 0.4f));
    ground0 = std::make_shared<ObjObject>("./resources/objects/blue_ground/ground.obj", glm::vec3(10.8f,0.2f, 10.8f));
    ground1 = std::make_shared<ObjObject>("./resources/objects/red_ground/ground.obj", glm::vec3(10.8f, 0.2f, 10.8f));
    ground2 = std::make_shared<ObjObject>("./resources/objects/yellow_ground/ground.obj", glm::vec3(10.8f, 0.2f, 10.8f));
    
    wallheight = WALL_HEIGHT;
    groundheight = GROUND_HEIGHT;
    wallwidth = WALL_WIDTH;
    groundsize = GROUND_SIZE;

    float offsetforwidth = wallwidth / 2.0f;

    std::vector<glm::vec3> wallsmin1 = std::vector<glm::vec3>();
    std::vector<glm::vec3> wallsmax1 = std::vector<glm::vec3>();
    const char* file1 = "./resources/scene/map_animal.txt";
    readWallsCoord(0, file1, wallsmin1, wallsmax1, glm::vec3(-(groundsize + offsetforwidth), 0.0f, offsetforwidth));

    glm::vec3 groundmin1 = glm::vec3(0.0f, -0.2f, 0.0f);
    glm::vec3 groundmax1 = glm::vec3(-groundsize - wallwidth, 0.0f, groundsize + wallwidth);
    map1 = new Submap(wallsmin1, wallsmax1, groundmin1, groundmax1);
    glm::mat4 trans1 = {
        {1,0,0,0},
        {0,1,0,0},
        {0.5,0,0.5 * glm::sqrt(3.0f),0},
        {0,0,0,1} };
    map1->setModel(trans1);

    std::vector<glm::vec3> wallsmin2 = std::vector<glm::vec3>();
    std::vector<glm::vec3> wallsmax2 = std::vector<glm::vec3>();
    const char* file2 = "./resources/scene/map_clown.txt";
    readWallsCoord(1, file2, wallsmin2, wallsmax2, glm::vec3(-(groundsize + offsetforwidth), 0.0f, -(groundsize + offsetforwidth)));

    glm::vec3 groundmin2 = glm::vec3(0.0f, -0.2f, 0.0f);
    glm::vec3 groundmax2 = glm::vec3(-(groundsize + wallwidth), 0.0f, -(groundsize + wallwidth));
    map2 = new Submap(wallsmin2, wallsmax2, groundmin2, groundmax2);
    glm::mat4 trans2 = {
        {1,0,0,0},
        {0,1,0,0},
        {-0.5,0,0.5 * glm::sqrt(3.0f),0},
        {0,0,0,1} };
    map2->setModel(trans2);

    std::vector<glm::vec3> wallsmin3 = std::vector<glm::vec3>();
    std::vector<glm::vec3> wallsmax3 = std::vector<glm::vec3>();
    const char* file3 = "./resources/scene/map_sculpture.txt";
    readWallsCoord(2, file3, wallsmin3, wallsmax3, glm::vec3(offsetforwidth, 0.0f, -(groundsize + offsetforwidth)));

    glm::vec3 groundmin3 = glm::vec3(0.0f, -0.2f, 0.0f);
    glm::vec3 groundmax3 = glm::vec3((groundsize + wallwidth), 0.0f, -(groundsize + wallwidth));
    map3 = new Submap(wallsmin3, wallsmax3, groundmin3, groundmax3);
    glm::mat4 trans3 = {
        {0.5,0,0.5 * glm::sqrt(3.0f),0},
        {0,1,0,0},
        {-0.5,0,0.5 * glm::sqrt(3.0f),0},
        {0,0,0,1} };
    map3->setModel(trans3);

    obs = new Obstacles();
    obs->obstacleCubes();
    glm::mat4 id_mat = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    for (int ind = 0; ind < obs->cubes.size(); ind++) {
        Cube* cub = obs->cubes[ind];
        ObsObject* obj = obs->obs_vec[ind];
        cub->setModel(this->getModelOnMap(id_mat, obj->map_id, (obj->pos).first, (obj->pos).second));
    }
    glm::mat4 model_for_ground = glm::mat4(1.0f);
    model_for_ground = getModelOnMap(model_for_ground, 0, 2.5f, 2.5f);
    model_for_ground *= map1->getModel();
    //model_for_ground *= glm::rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //std::cout << glm::to_string(model_for_ground) << std::endl;
    ground0->setModel(model_for_ground);

    model_for_ground = glm::mat4(1.0f);
    model_for_ground = getModelOnMap(model_for_ground, 1, 2.5f, 2.5f);
    model_for_ground *= map2->getModel();
    //model_for_ground *= glm::rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //std::cout << glm::to_string(model_for_ground) << std::endl;
    ground1->setModel(model_for_ground);

    model_for_ground = glm::mat4(1.0f);
    model_for_ground = getModelOnMap(model_for_ground, 2, 2.5f, 2.5f);
    model_for_ground *= map3->getModel();
    //model_for_ground *= glm::rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //std::cout << glm::to_string(model_for_ground) << std::endl;
    ground2->setModel(model_for_ground);
    
}

Map::~Map() {
    delete map1;
    delete map2;
    delete map3;
}

void Map::readWallsCoord(int mapId, const char* file, std::vector<glm::vec3>& wallsmin, std::vector<glm::vec3>& wallsmax, glm::vec3 translation) {
    Tokenizer token = Tokenizer();
    char temp[256];
    token.Open(file);
    float walllength = groundsize / 5.0f;
    float offsetforwidth = wallwidth / 2.0f;
    //std::cout<<"offset "<<offsetforwidth<<std::endl;
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            int tempint = token.GetInt();
            MAP_ENCODING[mapId][j][i] = tempint;
            //std::cout<<"int "<<tempint<<std::endl;
            glm::vec3 topwallmin = glm::vec3(i * walllength - offsetforwidth, 0.0f, j * walllength - offsetforwidth) + translation;
            glm::vec3 topwallmax = glm::vec3((i + 1) * walllength + offsetforwidth, wallheight, j * walllength + offsetforwidth) + translation;
            glm::vec3 leftwallmin = glm::vec3(i * walllength - offsetforwidth, 0.0f, j * walllength - offsetforwidth) + translation;
            glm::vec3 leftwallmax = glm::vec3((i)*walllength + offsetforwidth, wallheight, (j + 1) * walllength + offsetforwidth) + translation;
            //std::cout<<"topwallmin "<<glm::to_string(topwallmin)<<std::endl;
            //std::cout<<"topwallmax "<<glm::to_string(topwallmax)<<std::endl;
            //std::cout<<"leftwallmin "<<glm::to_string(leftwallmin)<<std::endl;
            //std::cout<<"leftwallmax "<<glm::to_string(leftwallmax)<<std::endl;
            if (tempint == 0) {
                continue;
            }
            else if (tempint == 1) {
                wallsmin.push_back(topwallmin);
                wallsmax.push_back(topwallmax);
                walls_left_top.push_back(true);
                walls.push_back(std::make_tuple(mapId, (float)i + 0.5f, (float)j));
            }
            else if (tempint == 2) {
                wallsmin.push_back(leftwallmin);
                wallsmax.push_back(leftwallmax);
                walls_left_top.push_back(false);
                walls.push_back(std::make_tuple(mapId, (float)i , (float)j+0.5f));
            }
            else if (tempint == 3) {
                wallsmin.push_back(topwallmin);
                wallsmax.push_back(topwallmax);
                wallsmin.push_back(leftwallmin);
                wallsmax.push_back(leftwallmax);
                walls.push_back(std::make_tuple(mapId, i + 0.5f, (float)j));
                walls.push_back(std::make_tuple(mapId, (float)i, (float)j + 0.5f));
                walls_left_top.push_back(true);
                walls_left_top.push_back(false);
            }
        }
    }
    //std::cout<<"get here"<<std::endl;
    token.Close();
}

void Map::update() {
    map1->update();
    map2->update();
    map3->update();
}

void Map::getPosition(glm::mat4& model, int* mapID, float* x, float* y) {
    const float* pSource = (const float*)glm::value_ptr(model);
    glm::vec4 position = glm::vec4(pSource[12], pSource[13], pSource[14], pSource[15]);
    float theta = atan2(-pSource[14], pSource[12]);
    float offsetforwidth = wallwidth / 2.0f;
    //std::cout<<"position "<<glm::to_string(position)<<std::endl;
    //std::cout<<"degree "<<theta<<std::endl;ß
    if (theta < 0) {
        theta = M_PI * 2 + theta;
    }
    glm::vec4 MapTranslation;
    if (theta<M_PI / 3 || theta>M_PI * 2 / 6 * 5) {
        *mapID = 2;
        position = glm::inverse(map3->getModel()) * position;
        MapTranslation = -glm::vec4(offsetforwidth, 0.0f, -(groundsize + offsetforwidth), 1.0f);
    }
    else if (theta < M_PI) {
        *mapID = 1;
        position = glm::inverse(map2->getModel()) * position;
        MapTranslation = -glm::vec4(-(groundsize + offsetforwidth), 0.0f, -(groundsize + offsetforwidth), 1.0f);
    }
    else {
        *mapID = 0;
        position = glm::inverse(map1->getModel()) * position;
        MapTranslation = -glm::vec4(-(groundsize + offsetforwidth), 0.0f, offsetforwidth, 1.0f);
    }
    position = position + MapTranslation;
    *x = glm::clamp((position.x) / groundsize * 5, 0.0f, 5.0f);
    *y = glm::clamp((position.z) / groundsize * 5, 0.0f, 5.0f);
    /*std::cout<<"mapID "<<*mapID<<std::endl;
    std::cout<<"x "<<*x<<std::endl;
    std::cout<<"y "<<*y<<std::endl;*/
}

std::vector<std::pair<float, float>> Map::getGrid(int mapID, float x, float y) {
    float x_min = x - COLLISION_CHECKER;
    float x_max = x + COLLISION_CHECKER;
    float y_min = y - COLLISION_CHECKER;
    float y_max = y + COLLISION_CHECKER;

    int onEdge = 0;
    if ((mapID == 0 && x_min < 0.0f)) {
        onEdge = 2;
    }
    else if (mapID == 0 && y_max > 5.0f) {
        onEdge = 3;
    }
    else if (mapID == 1 && x_max > 5.0f) {
        onEdge = 1;
    }
    else if (mapID == 2 && x_max > 5.0f) {
        onEdge = 4;
    }
    std::vector<glm::vec4> points = std::vector<glm::vec4>();
    std::vector<std::pair<float, float>> results = std::vector<std::pair<float, float>>();

    if (onEdge == 1) {
        points.push_back(getPointsCollision(1, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(1, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(1, 5.0f - x, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(1, 5.0f - x, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        float y_off = (5.0f - x) / sqrt(3) * 2;
        points.push_back(getPointsCollision(0, 5.0f - x, -COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x - 5.0f, 0));
        points.push_back(getPointsCollision(0, 5.0f - x, COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x - 5.0f, 0));
        points.push_back(getPointsCollision(0, x_max - x, -COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x - 5.0f, 0));
        points.push_back(getPointsCollision(0, x_max - x, COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x - 5.0f, 0));
    }
    else if (onEdge == 2) {
        float y_off = (x) / sqrt(3) * 2;
        points.push_back(getPointsCollision(1, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x + 5.0f, 0));
        points.push_back(getPointsCollision(1, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x + 5.0f, 0));
        points.push_back(getPointsCollision(1, 0.0f - x, -COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x + 5.0f, 0));
        points.push_back(getPointsCollision(1, 0.0f - x, COLLISION_CHECKER) + glm::vec4(y + y_off, 0, x + 5.0f, 0));

        points.push_back(getPointsCollision(0, 0.0f - x, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(0, 0.0f - x, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(0, COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(0, COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
    }
    else if (onEdge == 3) {

        points.push_back(getPointsCollision(0, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(0, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(0, COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(0, COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));

        points.push_back(getPointsCollision(2, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(x, 0, 10.0f - y, 0));
        points.push_back(getPointsCollision(2, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(x, 0, 10.0f - y, 0));
        points.push_back(getPointsCollision(2, COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(x, 0, 10.0f - y, 0));
        points.push_back(getPointsCollision(2, COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(x, 0, 10.0f - y, 0));

    }
    else if (onEdge == 4) {

        points.push_back(getPointsCollision(0, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(10.0f - x, 0, y, 0));
        points.push_back(getPointsCollision(0, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(10.0f - x, 0, y, 0));
        points.push_back(getPointsCollision(0, COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(10.0f - x, 0, y, 0));
        points.push_back(getPointsCollision(0, COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(10.0f - x, 0, y, 0));

        points.push_back(getPointsCollision(2, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(2, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(2, COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(2, COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));


    }
    else {
        points.push_back(getPointsCollision(mapID, -COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(mapID, -COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(mapID, COLLISION_CHECKER, -COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
        points.push_back(getPointsCollision(mapID, COLLISION_CHECKER, COLLISION_CHECKER) + glm::vec4(y, 0, x, 0));
    }
    // std::cout<<"edge " <<onEdge<<std::endl;
    for (int i = 0; i < points.size(); i++) {

        if (fabs(points.at(i).z) < 0.001) {
            points.at(i).z = 0.0f;
        }
        else if ((fabs(points.at(i).z - 5.0f) < 0.001)) {
            points.at(i).z = 5.0f;
        }
        if (fabs(points.at(i).x) < 0.001) {
            points.at(i).x = 0.0f;
        }
        else if ((fabs(points.at(i).x - 5.0f) < 0.001)) {
            points.at(i).x = 5.0f;
        }
        results.push_back(std::make_pair(points.at(i).z, points.at(i).x));
        // std::cout <<"x "<<results.at(i).first<<" ";
        // std::cout <<"y "<<results.at(i).second<<" "<<std::endl;
    }
    /*if(points.size()==8){
        for(int i=0;i<points.size();i++){
            std::cout <<"x "<<results.at(i).first<<" ";
            std::cout <<"y "<<results.at(i).second<<" "<<std::endl;
        }
        std::cout <<" "<<std::endl;
    }*/

    return results;
}

glm::vec4 Map::getPointsCollision(int mapID, float x, float y) {
    glm::vec4 point = glm::vec4(y, 0.0f, x, 1.0f);
    if (mapID == 0) {
        return glm::inverse(map1->getModel()) * point;
    }
    else if (mapID == 1) {
        return glm::inverse(map2->getModel()) * point;
    }
    else {
        return glm::inverse(map2->getModel()) * point;
    }
    //glm::vec4 point=glm::vec4(0.0f);
}

glm::mat4 Map::getModelOnMap(glm::mat4& original, int mapID, float x, float y)
{
    float walllength = groundsize / 5.0f;
    glm::vec4 position = glm::vec4(x * walllength, 0.0f, y * walllength, 0.0f);
    glm::vec4 MapTranslation;
    float offsetforwidth = wallwidth / 2.0f;
    if (mapID == 2) {
        MapTranslation = glm::vec4(offsetforwidth, 0.0f, -(groundsize + offsetforwidth), 1.0f);
        position = position + MapTranslation;
        position = (map3->getModel()) * position;

    }
    else if (mapID == 1) {
        MapTranslation = glm::vec4(-(groundsize + offsetforwidth), 0.0f, -(groundsize + offsetforwidth), 1.0f);
        position = position + MapTranslation;
        position = (map2->getModel()) * position;
    }
    else {
        MapTranslation = glm::vec4(-(groundsize + offsetforwidth), 0.0f, offsetforwidth, 1.0f);
        position = position + MapTranslation;
        position = (map1->getModel()) * position;
    }
    float* pSource = (float*)glm::value_ptr(original);
    pSource[12] = position[0];
    pSource[13] = position[1];
    pSource[14] = position[2];
    return glm::make_mat4(pSource);
}


void Map::draw(const glm::mat4& viewProjMtx, GLuint shader, std::vector<int> os, std::vector<glm::mat4>& sobs_pos, std::vector<glm::mat4>& mobs_pos, std::vector<glm::mat4>& lobs_pos) {
    map1->draw(viewProjMtx, shader);
    map2->draw(viewProjMtx, shader);
    map3->draw(viewProjMtx, shader);

    obs->draw(viewProjMtx, shader, os, sobs_pos, mobs_pos, lobs_pos);
}

void Map::draw(const glm::mat4& projection, const glm::mat4& view, StaticShader& shader) {
    for (int i = 0; i < walls.size(); i++) {
        glm::mat4 model_for_wall = glm::mat4(1.0f);
        model_for_wall=getModelOnMap(model_for_wall, get<0>(walls[i]), get<1>(walls[i]), get<2>(walls[i]));
        int mapId = get<0>(walls[i]);
        if (!walls_left_top[i]) {
            if (mapId == 0) {
                //model_for_wall *= map1->getModel();
                model_for_wall *= glm::rotate(glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            else if (mapId == 1) {
                //model_for_wall *= map2->getModel();
                model_for_wall *= glm::rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            else {
                //model_for_wall *= map3->getModel();
                model_for_wall *= glm::rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        else {
            if (mapId == 2) {
                //model_for_wall *= map1->getModel();
                model_for_wall *= glm::rotate(glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        /*if (!walls_left_top[i]) {
            model_for_wall *= glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }*/
        objObjectWall->setModel(model_for_wall);
        objObjectWall->draw(projection, view, shader);
       
    }
    
    //grd0model *= map1->getModel();
    
    ground0->draw(projection, view, shader);
    ground1->draw(projection, view, shader);
    ground2->draw(projection, view, shader);
}

glm::vec3 Map::calculateLightcenter(glm::mat4 model) {
    float x, y;
    int mapID;
    getPosition(model, &mapID, &x, &y);
    x = (int)x + 0.5f;
    y = (int)y + 0.5f;
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 newPosition = getModelOnMap(identity, mapID, x, y);
    float* pSource = (float*)glm::value_ptr(newPosition);
    return glm::vec3(pSource[12], pSource[13], pSource[14]);
}

std::vector<glm::vec3> Map::calculateBCDLightcenter() {
    std::vector<glm::vec3> result = std::vector<glm::vec3>();
    for (int mapID = 0; mapID < 3; mapID++) {
        glm::mat4 identity = glm::mat4(1.0f);
        glm::mat4 newPosition = getModelOnMap(identity, mapID, 2.5, 2.5);
        float* pSource = (float*)glm::value_ptr(newPosition);
        result.push_back(glm::vec3(pSource[12], pSource[13], pSource[14]));
    }
    return result;
}