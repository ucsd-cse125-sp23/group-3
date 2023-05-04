#pragma once

#include <vector>
#include "core.h"
#include "Camera.h"
#include <StaticShader.h>

class graphic2D {
    private:
        GLuint VAO;
        GLuint VBO, EBO;
        unsigned int texture;

        float sizeX;
        float sizeY;
        float positionX;
        float positionY;
        bool texturemapping;
        unsigned char *data;
        glm::vec3 color;
        std::vector<float> vertices;

    public:
        graphic2D(float _sizeX,float _sizeY, float _positionX, float _positionY, bool _texturemapping);
        ~graphic2D();

        void bindTexture(const char* filename);
        void draw(StaticShader shader);
        void update();
        void setColor(glm::vec3 _color);
        void setposition(float _sizeX, float _sizeY, float _positionX, float _positionY);
        void setposition(float _sizeX, float _sizeY);
        float getSizeX();
        float getSizeY();
        float getPosiX();
        float getPosiY();
};