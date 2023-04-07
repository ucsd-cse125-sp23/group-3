#pragma once

#include <vector>
#include <string>

#include "core.h"
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"

class Joint {
    private:
        std::string name;
        glm::mat4 local;
        glm::mat4 world;
        glm::mat4 bind;
        glm::vec3 offset;
        DOF* dofs;
        Cube* jnt;
        int num;

        // Joint Information
        std::vector<Joint*> children;
        Joint *parent;
        static std::vector<Joint*> Jointlist;
        
    public:
        Joint(std::string name, Joint *parent);
        ~Joint();
        
        static std::vector<Joint*> getList();
        DOF* getDOF();
        void setOffset(float data,int x);
        void setbind(glm::mat4 mat);
        void SetBox(glm::vec3 boxmin, glm::vec3 boxmax);
        void setModel(glm::vec3 deg, glm::vec3 offset);
        std::string getname();
        glm::mat4 getBind();
        void draw(const glm::mat4& viewProjMtx, GLuint shader);
        void update(glm::mat4 parent);
        bool load(Tokenizer &t);
};