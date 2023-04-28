#include "Window.h"
#include "DynamicModel.h"
#include <StaticShader.h>

#include "ObjObject.h"
#include <animation.h>
#include <animator.h>

#include <DaeObject.h>
// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "Model Environment";

// Objects to render
Map* Window::map;
UI* Window::ui;
DynamicModel* ourModel;
ObjObject* objObject1;
DaeObject* daeObject1;
Cube* Window::cube;
int Window::eventChecker;
int  Window::playerID;
// Camera Properties
Camera* Cam;
std::vector<Cube*> Window::players=std::vector<Cube*>(4);

Animation* animation;
Animator* animator;

// Interaction Variables
bool LeftDown, RightDown;
int MouseX, MouseY;
const float cameraSpeed = 0.15f;
const float turningratio=20.0f;
DynamicShader* dynamicShader;
StaticShader* staticShader;
StaticShader* uiShader;
graphic2D* Window::canvas;
Shader* Window::shaderText2DProgram;
std::vector<DaeObject*> daeObjectList;
std::vector<ObjObject*> objObjectList;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// The shader program id
GLuint Window::shaderProgram;
CollisionDetection collisionDetection;

// Constructors and desctructors
bool Window::initializeProgram() {
    std::cout << "ERROR HERE\n";
    // Create a shader program with a vertex shader and a fragment shader.
    shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");

    dynamicShader = new DynamicShader(Constants::dynamic_shader_vert, Constants::dynamic_shader_frag);
    staticShader = new StaticShader(Constants::static_shader_vert, Constants::static_shader_frag);

    uiShader = new StaticShader(Constants::ui_shader_vert, Constants::ui_shader_frag);
    shaderText2DProgram = new Shader("./shaders/texture2D.vs", "./shaders/texture2D.fs");
    // Check the shader program.
    if (!shaderProgram) {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }

    return true;
}

bool Window::initializeObjects(int PlayID) {
    // Create a cube
    map = new Map();
    ui = new UI();
    canvas = new graphic2D(0.8, 0.3, -0.4, 0.7, true);
    const char* textfile = "./resources/images/tag.png";
    canvas->bindTexture(textfile);
    //cube->move(2.0f);
    // cube = new Cube(glm::vec3(-1, 0, -2), glm::vec3(1, 1, 1));
    for (int i = 0; i < 4; i++) {
        Cube* temp = new Cube();
        players.at(i)=temp;
    }
    playerID = PlayID;
    daeObject1 = new DaeObject(Constants::girl_model_path,
        Constants::girl_walking_animation_path,
        Constants::girl_action_animation_path,
        glm::vec3(5.0f));
    objObject1 = new ObjObject("./resources/objects/ucsd_asset/bear.obj", glm::vec3(0.4f, 0.4f, 0.4f));

    daeObjectList.push_back(daeObject1);

    cube = new Cube();
    //cube->spin(180);
    //cube->move(-30.0f);
    //Cam->SetSpin(180);
    //Cam->SetMove(-30.0f);
    return true;
}

void Window::cleanUp() {
    // Deallcoate the objects.
    //delete cube;
    //delete ground;
    /*for (int i = 0; i < 4; i++) {
        delete players.at(i);
    }*/
    delete map;
    // Delete the shader program.
    glDeleteProgram(shaderProgram);
}

// for the Window
GLFWwindow* Window::createWindow(int width, int height) {
    // Initialize GLFW.
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    // 4x antialiasing.
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Apple implements its own version of OpenGL and requires special treatments
    // to make it uses modern OpenGL.
    // Ensure that minimum OpenGL version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable forward compatibility and allow a modern OpenGL context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the GLFW window.
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

    // Check if the window could not be created.
    if (!window) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the context of the window.
    glfwMakeContextCurrent(window);

    // Set swap interval to 1.
    glfwSwapInterval(0);

    // set up the camera
    
    Cam = new Camera();
    
    Cam->SetAspect(float(width) / float(height));

    // initialize the interaction variables
    LeftDown = RightDown = false;
    MouseX = MouseY = 0;

    // Call the resize callback to make sure things get drawn immediately.
    Window::resizeCallback(window, width, height);

    return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height) {
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size.
    glViewport(0, 0, width, height);

    Cam->SetAspect(float(width) / float(height));
}

// update and draw functions
void Window::idleCallback() {
    // Perform any updates as necessary.
    
    if (playerID == 0) {

        //Cam->setFirstperson();
    }
    if (!Constants::offline) {
        Cam->SetModel(players.at(playerID)->getModel());
    }
    
    Cam->Update();
    map->update();
    int mapID;
    float x, y;

    //cube->update();
}

void Window::displayCallback(GLFWwindow* window) {
    // Clear the color and depth buffers.
    
    float currentFrame = glfwGetTime();


    //std::cerr << deltaTime << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Render the object.
    //cube->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    //ground->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    map->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    ui->draw(Cam->GetViewProjectMtx(), *uiShader);
    if (Constants::offline) {
        daeObject1->draw(Cam->GetProjectMtx(), Cam->GetViewMtx(), *dynamicShader);
    }
    else {
        for (int i = 0; i < 4; i++) {
            players.at(i)->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
        }
    }
    canvas->draw(glm::mat4(1.0f), *shaderText2DProgram);
    // Draw static objObject
    //objObject1->draw(Cam->GetProjectMtx(), Cam->GetViewMtx(), *staticShader);

    //cube->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);

    //int mapID;
    //float x, y;
    //map->getPosition(cube->getModel(), &mapID, &y, &x);

    //std::vector<std::pair<float, float>> points = map->getGrid(mapID, x, y);
    //if (collisionDetection.checkCollisionWithWall(mapID, points)) {
    //     std::cerr<<"colliding!"<<std::endl;
    //    Cam->SetMove(cameraSpeed);
    //    cube->move(cameraSpeed);
    //}

    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

// helper to reset the camera
void Window::resetCamera() {
    //Cam->Reset();
    Cam->SetAspect(float(Window::width) / float(Window::height));
}
// callbacks - for Interaction
void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*
     * TODO: Modify below to add your key callbacks.
     */
    eventChecker = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Cam->SetMove(-cameraSpeed);
        cube->move(-cameraSpeed);
        //cube->move(-cameraSpeed);
        if (Constants::offline) {
            players.at(playerID)->move(-cameraSpeed);
            glm::mat4 newMVP = daeObject1->calculateMoveMVP(-cameraSpeed);
            daeObject1->setModel(newMVP);
        }
        eventChecker = 1;
    }

        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Cam->SetSpin(cameraSpeed*turningratio);
        cube->spin(cameraSpeed*turningratio);
        //cube->spin(cameraSpeed*turningratio);
        if (Constants::offline) {
            players.at(playerID)->spin(cameraSpeed * turningratio);
            daeObject1->spin(cameraSpeed * turningratio);
        }
        eventChecker = 2;

    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        Cam->SetSpin(-cameraSpeed*turningratio);
        //backPackObjectspin(-cameraSpeed * turningratio);
        cube->spin(-cameraSpeed*turningratio);
        if (Constants::offline) {
            players.at(playerID)->spin(-cameraSpeed * turningratio);
            daeObject1->spin(-cameraSpeed * turningratio); 
        }
        eventChecker = 3;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        daeObject1->doAction();
    }

    // Check for a key press.
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;

        /*case GLFW_KEY_R:
            resetCamera();
            break;
        */
        default:
            break;
        }
    }
}

void Window::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        LeftDown = (action == GLFW_PRESS);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        RightDown = (action == GLFW_PRESS);
    }
}

void Window::cursor_callback(GLFWwindow* window, double currX, double currY) {
    int maxDelta = 100;
    int cameraspeed = 100;
    int dx = glm::clamp((int)currX - MouseX, -maxDelta, maxDelta);
    int dy = glm::clamp(-((int)currY - MouseY), -maxDelta, maxDelta);

    MouseX = (int)currX;
    MouseY = (int)currY;

    // Move camera
    // NOTE: this should really be part of Camera::Update()
    /*if(KeyRightDown){
        //Cam->SetAzimuth(Cam->GetAzimuth()+cameraspeed);
        cube->spin(cameraspeed/100.0f);
    }
    if(KeyLeftDown){
        //Cam->SetAzimuth(Cam->GetAzimuth()-cameraspeed);
        cube->spin(-cameraspeed/100.0f);
    }
    if(KeyUpDown){
        //Cam->SetOffsetIncrement(cameraspeed);
        cube->move(cameraspeed/100.0f);
    }
    if(KeyDownDown){
        //Cam->SetOffsetDecrement(cameraspeed);
        cube->move(-cameraspeed/100.0f);
    }*/
}



