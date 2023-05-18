////////////////////////////////////////
// Camera.h
////////////////////////////////////////

#pragma once

#include "core.h"
#include "glm/gtx/euler_angles.hpp"

// The Camera class provides a simple means to controlling the 3D camera. It could
// be extended to support more interactive controls. Ultimately. the camera sets the
// GL projection and viewing matrices.

class Camera {
public:
    Camera();

    void Update();
    void Reset();

    // Access functions
    void SetAspect(float a) { Aspect = a; }
    void SetMove(float i){model = glm::translate(model, glm::vec3(0,0,i));};
    void SetSpin(float deg){model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));};
    void setModel(glm::mat4 _model){model=_model;};
    glm::vec3 GetCamTarget(){return CameraTar;};

    const glm::mat4 &GetViewProjectMtx() { return ViewProjectMtx; }
    glm::vec3 CameraPos, CameraTar;
    glm::mat4 Projection;

private:
    // Perspective controls
    float FOV;       // Field of View Angle (degrees)
    float Aspect;    // Aspect Ratio
    float NearClip;  // Near clipping plane distance
    float FarClip;   // Far clipping plane distance
    // Polar controls
    glm::vec3 CameraUp,CameraDir;
    // Computed data
    
    glm::mat4 model,ViewProjectMtx;
};