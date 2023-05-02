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

        void draw(const glm::mat4& viewProjMtx, StaticShader shader);
        void setPosition(glm::mat4 model);
        void update();
        graphic2D* getMinimap();
        void setposition(float _sizeX, float _sizeY, float _positionX, float _positionY);

        void setPersonX(float personx) {
            this->personx = personx;
        }
        void setPersonY(float persony) {
            this->persony = persony;
        }
        float getSizeX() {
            return sizeX;
        }
};