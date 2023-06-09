////////////////////////////////////////
// Camera.cpp
////////////////////////////////////////

#include "Camera.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include <glm/glm.hpp>

bool first_pers=true;
Camera::Camera() {
    Reset();
}
void Camera::Update() {
    // Compute camera world matrix
    glm::mat4 view;
    glm::vec4 tempTar=model*glm::vec4(CameraTar,1);
    glm::vec4 tempPos=model*glm::vec4(CameraPos,1);
    
    
    glm::vec3 upTar,upPos;
    upTar.x=tempTar.x;
    upTar.y=tempTar.y;
    upTar.z=tempTar.z;

    if(first_pers){
        upPos.x=tempPos.x;
        upPos.y=tempPos.y;
        upPos.z=tempPos.z;
    }
    else{
        upPos=upTar+CameraDir;
    }

    

    //std::cout<<glm::to_string(tempTar)<<std::endl;
    view = glm::lookAt(upPos, upTar, CameraUp);
    //glm::mat4 world(1);
    

    // Compute view matrix (inverse of world matrix)
    //glm::mat4 view = glm::inverse(world);

    // Compute perspective projection matrix
    
    
    glm::mat4 project = glm::perspective(glm::radians(FOV), Aspect, NearClip, FarClip);
    if(first_pers){
       // std::cout<<glm::to_string(glm::vec3(upPos-upTar))<<std::endl;
        auto axis=glm::cross(glm::normalize(glm::vec3(upPos-upTar)),glm::vec3(0.0f,0.0f,1.0f));
        auto angle=glm::acos(glm::dot(glm::normalize(glm::vec3(upPos-upTar)),glm::vec3(0.0f,0.0f,1.0f)));
        Projection=glm::rotate(-angle,axis);
    }else{
        Projection=glm::lookAt(glm::vec3(0.0f),CameraDir , CameraUp);
    }
    Projection=project;
    // Compute final view-projection matrix
    ViewProjectMtx = project * view;
}
void Camera::Reset() {
    FOV = 45.0f;
    Aspect = 1.33f;
    NearClip = 0.1f;
    FarClip = 100.0f;

    model=glm::mat4(1);

    //first perspective
    if(first_pers){
        CameraTar=glm::vec3(0.0f,2.0f,0.0f); 
        CameraDir=glm::vec3(0.0f,0.0f,1.0f);  
        CameraPos=CameraTar+CameraDir;
    }
    else{
        CameraTar=glm::vec3(0.0f,0.0f,0.0f); 
        CameraDir=glm::vec3(0.0f,30.0f,10.0f);  
    }
    //third perspective
    //std::cout<<glm::to_string(CameraPos)<<std::endl;
    //TODO:: change back to glm::vec3(0.0f,1.0f,0.0f); for later use
    CameraUp=glm::vec3(0.0f,1.0f,0.0f);
}