#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Map.h"
#include "graphic2D.h"
#include "Minimap.h"
#include "CollisionDetection.h"
#include "Shader.h"
#include "core.h"
#include <iostream>
#include "Mult_Lights.h"
#include "Particles.h"
#include "AliceSkill.h"

class Window {
public:
    // Window Properties
    static int width;
    static int height;
    static const char* windowTitle;

    // Objects to render
    static Cube* cube;
    static Map* map;
    static Minimap* canvas;
    static Particles* particles;

    // Shader Program
    static GLuint shaderProgram;
    static Shader* shaderText2DProgram;

    // Act as Constructors and desctructors
    static bool initializeProgram();
    static bool initializeObjects();
    static void cleanUp();
    static Mult_Lights* lights;

    // for the Window
    static GLFWwindow* createWindow(int width, int height);
    static void resizeCallback(GLFWwindow* window, int width, int height);

    // update and draw functions
    static void idleCallback();
    static void displayCallback(GLFWwindow*);

    // helper to reset the camera
    static void resetCamera();

    // callbacks - for interaction
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_callback(GLFWwindow* window, double currX, double currY);
};