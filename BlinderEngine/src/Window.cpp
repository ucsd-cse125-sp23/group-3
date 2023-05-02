#include "Window.h"
#include "DynamicModel.h"
#include <StaticShader.h>

#include "ObjObject.h"
#include <animation.h>
#include <animator.h>
#include <Skybox.h>
#include <DaeObject.h>
// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "Model Environment";

// Objects to render
Map* Window::map;
UI* Window::ui;
Cube* Window::cube;
std::vector<Cube*> Window::players = std::vector<Cube*>(4);
ObjObject* objObject1;
DaeObject* daeObject1;
std::vector<DaeObject*> daeObjectList;
std::vector<ObjObject*> objObjectList;
Skybox* skybox;

// Camera Properties
Camera* Cam;


// Interaction Variables
bool LeftDown, RightDown;
int MouseX, MouseY;
const float cameraSpeed = 1.5f;
const float turningratio=20.0f;

// Shaders
DynamicShader* dynamicShader;
StaticShader* staticShader;
//StaticShader* uiShader;
StaticShader* skyboxShader;

Shader* uiShader;
graphic2D* Window::canvas;



// Client-server
std::vector<int> Window::eventChecker = std::vector<int>(NUM_EVENT_TYPES, 0);
bool Window::no_event;
int  Window::playerID;
Shader* Window::uiShader;
//graphic2D* Window::canvas;
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
    // Create a shader program with a vertex shader and a fragment shader.
    shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");

    dynamicShader = new DynamicShader(Constants::dynamic_shader_vert, Constants::dynamic_shader_frag);
    staticShader = new StaticShader(Constants::static_shader_vert, Constants::static_shader_frag);
    //uiShader = new StaticShader(Constants::ui_shader_vert, Constants::ui_shader_frag);
    skyboxShader = new StaticShader("./shaders/skybox.vs", "./shaders/skybox.fs");
    skyboxShader->use();
    skyboxShader->setInt("skybox", 0);

    uiShader = new Shader(Constants::ui_shader_vert.c_str(), Constants::ui_shader_frag.c_str());
    
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
    skybox = new Skybox();
    canvas = new graphic2D(0.8, 0.3, -0.4, 0.7, true);
    const char* textfile = "./resources/images/tag.png";
    canvas->bindTexture(textfile);
    //ui->setDaeObj(daeObject1);
    
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
        glm::vec3(2.0f));

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
    delete ui;
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
    if (Window::ui != NULL) {
        Window::ui->setSize(width, height);
    }
    // Set the viewport size.
    glViewport(0, 0, width, height);

    Cam->SetAspect(float(width) / float(height));
}

// update and draw functions
void Window::idleCallback() {
    // Perform any updates as necessary.
    
    if (playerID == 0) {

        Cam->setFirstperson();
    }
    if (!Constants::offline) {
        Cam->SetModel(players.at(playerID)->getModel());
        
    }
    else {
        ui->setPlayerPosition(daeObject1->getModel());
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
    
    if (Constants::offline) {
        daeObject1->draw(Cam->GetProjectMtx(), Cam->GetViewMtx(), *dynamicShader);
    }
    else {
        for (int i = 0; i < 4; i++) {
            players.at(i)->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
        }
    }
    canvas->draw(glm::mat4(1.0f), *uiShader);



    ui->draw(Cam->GetViewProjectMtx(), *uiShader);
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
    //glm::mat4 projection = glm::perspective(glm::radians(Cam->getFOV()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    skybox->draw(Cam->GetProjectMtx(), Cam->GetViewMtx(), *skyboxShader);

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
    std::fill(eventChecker.begin(), eventChecker.end(), 0);
    no_event = true;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Cam->SetMove(-cameraSpeed);
        cube->move(-cameraSpeed);
        //cube->move(-cameraSpeed);
        if (Constants::offline) {
            players.at(playerID)->move(-cameraSpeed);
            glm::mat4 newMVP = daeObject1->calculateMoveMVP(-cameraSpeed);
            daeObject1->setModel(newMVP);
        }
        eventChecker[0] = 1;
        no_event = false;
    }

        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Cam->SetSpin(cameraSpeed*turningratio);
        cube->spin(cameraSpeed*turningratio);
        //cube->spin(cameraSpeed*turningratio);
        if (Constants::offline) {
            players.at(playerID)->spin(cameraSpeed * turningratio);
            daeObject1->spin(cameraSpeed * turningratio);
        }
        eventChecker[1] = 1;
        no_event = false;
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        Cam->SetSpin(-cameraSpeed*turningratio);
        //backPackObjectspin(-cameraSpeed * turningratio);
        cube->spin(-cameraSpeed*turningratio);
        if (Constants::offline) {
            players.at(playerID)->spin(-cameraSpeed * turningratio);
            daeObject1->spin(-cameraSpeed * turningratio); 
        }
        eventChecker[2] = 1;
        no_event = false;
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



