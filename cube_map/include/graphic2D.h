#pragma once

#include <vector>

#include "core.h"
#include "Camera.h"


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

        void setposition(float _sizeX,float _sizeY, float _positionX, float _positionY);
        void bindTexture(const char* filename);
        void draw(const glm::mat4& viewProjMtx, Shader shader);
        void update();
        void setColor(glm::vec3 _color);
};