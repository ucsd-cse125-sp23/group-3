
#include <string>
#include <iostream>
#include "graphic2D.h"


graphic2D::graphic2D(float _sizeX,float _sizeY, float _positionX, float _positionY, bool _texturemapping){
        sizeX=_sizeX;
        sizeY = _sizeY;
        positionX=_positionX;
        positionY=_positionY;
        texturemapping=_texturemapping;
        vertices = {
                // positions          // colors           // texture coords
                positionX+sizeX,  positionY+sizeY, 0.0f,    1.0f, 0.0f,   // top right
                positionX+sizeX, positionY, 0.0f,           1.0f, 1.0f,   // bottom right
                positionX, positionY, 0.0f,                 0.0f, 1.0f,   // bottom left
                positionX, positionY+sizeY, 0.0f,           0.0f, 0.0f    // top left 
        };
        unsigned int indices[] = {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (vertices.size()) * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindVertexArray(0);

}

graphic2D::~graphic2D(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
}

void graphic2D::setColor(glm::vec3 _color){
        color=_color;
}

void graphic2D::bindTexture(const char* filename){
        
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        int width, height, nrComponents;
        Image* newimg = new Image();
        newimg->load(filename, width, height, nrComponents, 0);
        // load and generate the texture
        data = newimg->getData();
        // load and generate the texture
        if (data){
                GLenum format;
                if (nrComponents == 1)
                format = GL_RED;
                else if (nrComponents == 3)
                format = GL_RGB;
                else if (nrComponents == 4)
                format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
        }
        else{
                std::cout << "Failed to load texture" << std::endl;
        }
        delete newimg;
}


void graphic2D::draw(StaticShader shader,float a){

        /*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
        glDisable(GL_DEPTH_TEST);*/
        //std::cout<<"make myself here"<<std::endl;
        if(texturemapping){
                //std::cout<<"make myself here"<<std::endl;
                
                //std::cout<<"make myself here"<<std::endl;
                //glUniformMatrix4fv(glGetUniformLocation(shader, "viewProj"), 1, false, (float*)&viewProjMtx);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBindTexture(GL_TEXTURE_2D, texture);
                
                shader.use();
                shader.setFloat("transparency", a);
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }else{

        }
        //std::cout<<"make myself here"<<std::endl;
        glEnable(GL_DEPTH_TEST);
        // Related to shaders and z value comparisons for the depth buffer.
        glDepthFunc(GL_LEQUAL);
}



void graphic2D::update(){
    vertices = {
        // positions                 // texture coords
        positionX + sizeX,  positionY + sizeY, 0.0f,    1.0f, 0.0f,   // top right
        positionX + sizeX, positionY, 0.0f,           1.0f, 1.0f,   // bottom right
        positionX, positionY, 0.0f,                 0.0f, 1.0f,   // bottom left
        positionX, positionY + sizeY, 0.0f,           0.0f, 0.0f    // top left 
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (vertices.size()) * sizeof(float), vertices.data());
}

void graphic2D::setposition(float _sizeX, float _sizeY, float _positionX, float _positionY) {
    sizeX = _sizeX;
    sizeY = _sizeY;
    positionX = _positionX;
    positionY = _positionY;
}

void graphic2D::setposition(float _sizeX, float _sizeY) {
    sizeX = _sizeX;
    sizeY = _sizeY;
}

float graphic2D::getSizeX() {
    return sizeX;
}

float graphic2D::getSizeY() {
    return sizeY;
}

float graphic2D::getPosiX() {
    return positionX;
}

float graphic2D::getPosiY() {
    return positionY;
}

