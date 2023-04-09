#pragma once

#include <vector>

#include "core.h"
#include"Vertex.h"
#include"Skeleton.h"
#include <glm/gtc/type_ptr.hpp>

class Skin {
    private:
        GLuint VAO;
        GLuint VBO_positions, VBO_normals, EBO;
        glm::mat4 model;
        Skeleton* skl;
        // Specify vertex positions
        glm::vec3 color;
        std::vector<Vertex*>vertices;
        
        // Specify indices
        std::vector<unsigned int> indices;
        std::vector<Joint*> jntlist;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;

    public:
        Skin(Skeleton* parent);
        ~Skin();

        void Load(const char* file);
        void updateVertex();
        void draw(const glm::mat4& viewProjMtx, GLuint shader);
};