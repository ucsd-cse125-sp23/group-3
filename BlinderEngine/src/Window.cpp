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

// Window state
WindowState Window::state;

// Objects to render
Map* Window::map;
UI* Window::ui;
graphic2D* Window::end_page;
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
StaticShader* skyboxShader;
StaticShader* Window::uiShader;
graphic2D* Window::landing_page;
graphic2D* Window::ready_btn;
Mult_Lights* Window::lights;



// Client-server
std::vector<int> Window::eventChecker = std::vector<int>(NUM_EVENT_TYPES, 0);
bool Window::no_event;
int  Window::playerID;
//StaticShader* Window::uiShader;
//graphic2D* Window::canvas;
StaticShader* Window::shaderText2DProgram;

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
    uiShader = new StaticShader(Constants::ui_shader_vert, Constants::ui_shader_frag);
    skyboxShader = new StaticShader("./shaders/skybox.vs", "./shaders/skybox.fs");
    skyboxShader->use();
    skyboxShader->setInt("skybox", 0);

    //uiShader = new StaticShader(Constants::ui_shader_vert.c_str(), Constants::ui_shader_frag.c_str());
    
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
    //lights = new Mult_Lights(PlayID==0);
    lights = new Mult_Lights(false);
    lights->AddLightBCD(map->calculateBCDLightcenter());
    ui = new UI();
    skybox = new Skybox();
    end_page = new graphic2D(2, 2, -1, -1, true);
    // canvas = new graphic2D(0.8, 0.3, -0.4, 0.7, true);
    const char* textfile = "./resources/images/tag.png";
    // canvas->bindTexture(textfile);
    //ui->setDaeObj(daeObject1);
    
    //cube->move(2.0f);
    // cube = new Cube(glm::vec3(-1, 0, -2), glm::vec3(1, 1, 1));
    for (int i = 0; i < 4; i++) {
        Cube* temp = new Cube();
        players.at(i)=temp;
    }
    playerID = PlayID;
    daeObject1 = new DaeObject("./resources/objects/alice/alice.dae",
        "./resources/objects/alice/animation/walking.dae",
        "./resources/objects/alice/animation/dancing.dae",
        glm::vec3(0.7f));

    objObject1 = new ObjObject("./resources/objects/ucsd_asset/bear.obj", glm::vec3(0.4f, 0.4f, 0.4f));

    daeObjectList.push_back(daeObject1);

    //cube->spin(180);
    //cube->move(-30.0f);
    //Cam->SetSpin(180);
    //Cam->SetMove(-30.0f);
    return true;
}

bool Window::initializeLanding() {
    state = WindowState::LANDING;
    landing_page = new graphic2D(2, 2, -1, -1, true);
    const char* landing_page_png = "./resources/images/test.png";
    landing_page->bindTexture(landing_page_png);

    ready_btn = new graphic2D(0.2, 0.2, 0.7, -0.7, true);
    const char* ready_btn_png = "./resources/images/test.png";
    ready_btn->bindTexture(ready_btn_png);
    return true;
}

void Window::drawLanding(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    landing_page->draw(*uiShader,1.0f);
    ready_btn->draw(*uiShader,1.0f);

    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
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
       
       //Cam->setFirstperson();
    }
    if (!Constants::offline) {
        lights->updateLightAlice(map->calculateLightcenter(players.at(playerID)->getModel()), true);
        Cam->SetModel(players.at(playerID)->getModel());
        ui->setPlayerPosition(players.at(playerID)->getModel());

    }
    else {
        ui->setPlayerPosition(daeObject1->getModel());
        lights->updateLightAlice(map->calculateLightcenter(daeObject1->getModel()), true);
    }
    
    Cam->Update();
    map->update();
    //lights->updateLightAliceV2(daeObject1->getModel());
    int mapID;
    float x, y;

    //cube->update();
}

void Window::displayCallback(GLFWwindow* window, std::vector<int> os) {
    // Clear the color and depth buffers.
    
    float currentFrame = glfwGetTime();


    //std::cerr << deltaTime << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lights->loadToUShader(shaderProgram, *Cam);
    lights->loadToDShader(*dynamicShader, *Cam);
    lights->loadToSShader(*staticShader, *Cam);
    // Render the object.
    //cube->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    //ground->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);



    map->draw(Cam->GetViewProjectMtx(), Window::shaderProgram, os);
    
    if (Constants::offline) {
        daeObject1->draw(Cam->GetProjectMtx(), Cam->GetViewMtx(), *dynamicShader);
    }
    else {
        for (int i = 0; i < 4; i++) {
            players.at(i)->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
        }
    }
    // canvas->draw(*uiShader);



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
    if (playerID != 0) {
        skybox->draw(Cam->GetProjectMtx(), Cam->GetViewMtx(), *skyboxShader);
    }
    

    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

void Window::setEndPage(GameState gs) {
    if (gs == GameState::WIN) {
        const char* win_page_png = "./images/win.png";
        end_page->bindTexture(win_page_png);
    }
    else if (gs == GameState::LOSE) {
        const char* lose_page_png = "./images/lose.png";
        end_page->bindTexture(lose_page_png);
    }
}

void Window::displayEndPage(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    end_page->draw(*uiShader,1.0f);

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
        //cube->move(-cameraSpeed);
        if (Constants::offline) {
            Cam->SetMove(-cameraSpeed);
            players.at(playerID)->move(-cameraSpeed);
            glm::mat4 newMVP = daeObject1->calculateMoveMVP(-cameraSpeed);
            daeObject1->setModel(newMVP);
        }
        eventChecker[(int)EventType::FORWARD - 1] = 1;
        no_event = false;
    }

        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //cube->spin(cameraSpeed*turningratio);
        if (Constants::offline) {
            Cam->SetSpin(cameraSpeed * turningratio);
            players.at(playerID)->spin(cameraSpeed * turningratio);
            daeObject1->spin(cameraSpeed * turningratio);
        }
        eventChecker[(int)EventType::TURN_LEFT - 1] = 1;
        no_event = false;
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //backPackObjectspin(-cameraSpeed * turningratio);
        if (Constants::offline) {
            Cam->SetSpin(-cameraSpeed * turningratio);
            players.at(playerID)->spin(-cameraSpeed * turningratio);
            daeObject1->spin(-cameraSpeed * turningratio); 
        }
        eventChecker[(int)EventType::TURN_RIGHT - 1] = 1;
        no_event = false;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        eventChecker[(int)EventType::ATTACK - 1] = 1;
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
    if (cursorOnReadyBtn(MouseX, MouseY) && LeftDown) {
        state = WindowState::INGAME;
        std::cout << "READY!!\n";
    }
}

void Window::cursor_callback(GLFWwindow* window, double currX, double currY) {
    int maxDelta = 100;
    int cameraspeed = 100;
    int dx = glm::clamp((int)currX - MouseX, -maxDelta, maxDelta);
    int dy = glm::clamp(-((int)currY - MouseY), -maxDelta, maxDelta);
    if (cursorOnReadyBtn(currX, currY)) {
        const char* ready_btn_png = "./resources/images/test2.png";
        ready_btn->bindTexture(ready_btn_png);
    }
    else {
        const char* ready_btn_png = "./resources/images/test.png";
        ready_btn->bindTexture(ready_btn_png);
    }

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

bool Window::cursorOnReadyBtn(double currX, double currY) {
    if (state != WindowState::LANDING) {
        return false;
    }
    //std::cout << currX << " " << currY << endl;
    //std::cout << posiX << " " << posiY << endl;
    if (width*1.7/2 < currX && currX < width*1.9/2 && height*1.5/2 < currY && currY < height*1.7/2) {
        //std::cout << "On ready btn\n";
        return true;
    }
    return false;
}

void Window::updateLevel(int curr) {
    ui->changeLevelbarSizeY((float)curr / (float)Constants::MAX_LEVEL);
}

void Window::updateTime(int curr) {
    ui->changeTimebarSizeY((float)curr / (float)GAME_LENGTH);
}

