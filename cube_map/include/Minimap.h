#pragma once

#include <vector>
#include <utility>
#include "core.h"
#include "Map.h"
#include "graphic2D.h"
#include "MapConstants.h"

class Minimap {
    private:

        graphic2D* minimap;
        graphic2D* person;
        float personx;
        float persony;
        Map* map;
        float sizeX;
        float sizeY;
        float positionX;
        float positionY;

    public:
        Minimap(float _sizeX,float _sizeY, float _positionX, float _positionY);
        ~Minimap();

        void draw(const glm::mat4& viewProjMtx, Shader shader);
        void setPosition(glm::mat4 model);
        void update();
};