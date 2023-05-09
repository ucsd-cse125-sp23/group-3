#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Ground.h"
#include "Map.h"
#include "UI.h"
#include "Shader.h"
#include "core.h"
#include <vector>
#include <graphic2D.h>
#include <CollisionDetection.h>
#include "../../shared/GlobalVariables.h"
#include <Skybox.h>
#include <Mult_Lights.h>

enum class WindowState
{
    LANDING = 0,
    INGAME = 1,
    ENDING = 2
};

class Window {
public:
    // Window Properties
    static int width;
    static int height;
    static const char* windowTitle;

    // Window state
    static WindowState state;

    // Objects to render  online
    static Map* map;
    static std::vector<Cube*> players;
    static graphic2D* landing_page;
    static graphic2D* ready_btn;
    static UI* ui;
    static graphic2D* end_page;
    static Mult_Lights* lights;
    // Shader
    static GLuint shaderProgram;


    // Client-server variable
    static std::vector<int> eventChecker;
    static bool no_event;
    static int playerID;
    //static graphic2D* canvas;
    static StaticShader* shaderText2DProgram;
    //static UI* ui;
    static StaticShader* uiShader;

    //static int eventChecker;
    //static int playerID;
    // Shader Program
    //static GLuint shaderProgram;

    int getWindowWidth() {
        return width;
    }
    int getWindowHeight() {
        return height;
    }

    // Act as Constructors and desctructors
    static bool initializeProgram();
    static bool initializeObjects(int PlayID);
    static bool initializeLanding();
    static void cleanUp();

    // for the Window
    static GLFWwindow* createWindow(int width, int height);
    static void resizeCallback(GLFWwindow* window, int width, int height);

    // update and draw functions
    static void idleCallback();
    static void drawLanding(GLFWwindow* window);
    static void displayCallback(GLFWwindow*, std::vector<int> os);
    static void setEndPage(GameState);
    static void displayEndPage(GLFWwindow*);

    // helper to reset the camera
    static void resetCamera();

    // callbacks - for interaction
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_callback(GLFWwindow* window, double currX, double currY);

    static bool cursorOnReadyBtn(double, double);

    static unsigned int loadCubemap(std::vector<std::string> faces);

    static void updateLevel(int);
    static void updateTime(int);
};