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
const char* Window::windowTitle = "The Invisiable One";
std::shared_ptr<Scene> Window::scene;
// Window state
WindowState Window::state;

// Objects to render

// Camera Properties


// Interaction Variables
bool LeftDown, RightDown;
int MouseX, MouseY;
const float cameraSpeed = 1.5f;
const float turningratio = 20.0f;

// Shaders



// Client-server
std::vector<int> Window::eventChecker = std::vector<int>(NUM_EVENT_TYPES, 0);
bool Window::no_event;
int  Window::playerID;
int  Window::acq_char_id = -1;
bool Window::toReady = false;
bool Window::clickRestart = false;
//StaticShader* Window::uiShader;
//graphic2D* Window::canvas;


// The shader program id

// Constructors and desctructors
bool Window::initializeProgram() {
    scene = std::make_shared<Scene>();

    return true;
}

bool Window::initializeObjects(int PlayID) {
    scene->init(PlayID);
    return true;
}

bool Window::initializeLanding() {
    // state = WindowState::LANDING;
    scene->initLandingPage();
    scene->loadLanding();
    return true;
}

bool Window::initializeCover()
{
    scene->initCover();
    return true;
}

void Window::cleanLanding() {
    // shared_ptr automaticly free up memory
}

void Window::drawLanding(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->drawLanding();

    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::cleanUp() {
    // TODO: delete objects

    // Delete the shader program.
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
    if (scene != nullptr)
    {
        scene->resizeScene(width, height);
    }
    // Set the viewport size.
}

// update and draw functions
void Window::idleCallback() {
    scene->updateWorld();
    // void Window::idleCallback(int awareness) {
    //     // Perform any updates as necessary.

    //     if (playerID == 0) {

    //        Cam->setFirstperson();
    //     }
    //     if (!Constants::offline) {
    //         lights->updateLightAlice(map->calculateLightcenter(players.at(playerID)->getModel()), true);
    //         Cam->SetModel(players.at(playerID)->getModel());
    //         ui->setPlayerPosition(players.at(playerID)->getModel());

    //     }
    //     else {
    //         if (awareness >= AWARENESS_THRESHOLD && playerID != 0)
    //         {
    //             // TODO(Crystal): draw Alice's location
    //         }
    //         ui->setPlayerPosition(daeObject1->getModel());
    //         lights->updateLightAlice(map->calculateLightcenter(daeObject1->getModel()), true);
    //     }

    //     Cam->Update();
    //     map->update();
    //     //lights->updateLightAliceV2(daeObject1->getModel());
    //     int mapID;
    //     float x, y;

    //     //cube->update();
}

void Window::displayCallback(GLFWwindow* window, std::vector<int> os, int cd_remain) {
    // Clear the color and depth buffers.

    //std::cerr << deltaTime << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->displayWorld(os, cd_remain);
    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::setEndPage(GameState gs) {
    if (gs == GameState::WIN) {
        scene->setEnd(true);
    }
    else if (gs == GameState::LOSE) {
        scene->setEnd(false);
    }
}

void Window::displayEndPage(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->drawEnd();

    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

void Window::diaplayCoverPage(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->drawCover();

    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

// helper to reset the camera
void Window::resetCamera() {
    //Cam->Reset();
    scene->setAspect(float(Window::width) / float(Window::height));
}

// callbacks - for Interaction
void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*
     * TODO: Modify below to add your key callbacks.
     */
    std::fill(eventChecker.begin(), eventChecker.end(), 0);
    no_event = true;
    clickRestart = false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //cube->move(-cameraSpeed);
        if (Constants::offline) {
            scene->move();
        }
        eventChecker[(int)EventType::FORWARD - 1] = 1;
        no_event = false;
    }


    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //cube->spin(cameraSpeed*turningratio);
        if (Constants::offline) {
            scene->spin(1);
        }
        eventChecker[(int)EventType::TURN_LEFT - 1] = 1;
        no_event = false;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //backPackObjectspin(-cameraSpeed * turningratio);
        if (Constants::offline) {
            scene->spin(-1);
        }
        eventChecker[(int)EventType::TURN_RIGHT - 1] = 1;
        no_event = false;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (Constants::offline) {
            scene->playersObjects[playerID]->doAttack();
        }
        eventChecker[(int)EventType::ATTACK - 1] = 1;
        no_event = false;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (Constants::offline)
        {
            scene->playersObjects[playerID]->doAction();
        }
        eventChecker[(int)EventType::SKILL - 1] = 1;
        no_event = false;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        clickRestart = true;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        scene->endScene();
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
    LeftDown = false;
    RightDown = false;
    acq_char_id = -1;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        LeftDown = (action == GLFW_PRESS);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        RightDown = (action == GLFW_PRESS);
    }
    if ((Constants::offline || toReady) && cursorOnReadyBtn(MouseX, MouseY) && LeftDown) {
        state = WindowState::INGAME;
        LeftDown = false;
        std::cout << "READY!!\n";
    }
    if (cursorOnABtn(MouseX, MouseY) && LeftDown) {
        acq_char_id = 0;
        LeftDown = false;
    }
    if (cursorOnBBtn(MouseX, MouseY) && LeftDown) {
        acq_char_id = 1;
        LeftDown = false;
    }
    if (cursorOnCBtn(MouseX, MouseY) && LeftDown) {
        acq_char_id = 2;
        LeftDown = false;
    }
    if (cursorOnDBtn(MouseX, MouseY) && LeftDown) {
        acq_char_id = 3;
        LeftDown = false;
    }

}

void Window::cursor_callback(GLFWwindow* window, double currX, double currY) {
    int maxDelta = 100;
    int cameraspeed = 100;
    int dx = glm::clamp((int)currX - MouseX, -maxDelta, maxDelta);
    int dy = glm::clamp(-((int)currY - MouseY), -maxDelta, maxDelta);
    if (toReady && cursorOnReadyBtn(currX, currY)) {
        //scene->updateReadyBtn("./resources/images/test2.png");
        scene->ready_state = 2;
    }
    else if (!toReady) {
        //scene->updateReadyBtn("./resources/images/testS.png");
        scene->ready_state = 0;
    }
    else {
        //scene->updateReadyBtn("./resources/images/test.png");
        scene->ready_state = 1;
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
    if (width * 1.7 / 2 < currX && currX < width * 1.9 / 2 && height * 1.5 / 2 < currY && currY < height * 1.7 / 2) {
        //std::cout << "On ready btn\n";
        return true;
    }
    return false;
}

bool Window::cursorOnABtn(double x, double y) {
    return state != WindowState::LANDING ||
        width * 0.1 / 2 < x && width * 0.3 / 2 > x &&
        height * 1.5 / 2 < y && y < height * 1.7 / 2;
}
bool Window::cursorOnBBtn(double x, double y) {
    return state != WindowState::LANDING ||
        width * 0.5 / 2 < x && width * 0.7 / 2 > x &&
        height * 1.5 / 2 < y && y < height * 1.7 / 2;
}
bool Window::cursorOnCBtn(double x, double y) {
    return state != WindowState::LANDING ||
        width * 0.9 / 2 < x && width * 1.1 / 2 > x &&
        height * 1.5 / 2 < y && y < height * 1.7 / 2;
}
bool Window::cursorOnDBtn(double x, double y) {
    return state != WindowState::LANDING ||
        width * 1.3 / 2 < x && width * 1.5 / 2 > x &&
        height * 1.5 / 2 < y && y < height * 1.7 / 2;
}

void Window::updateLevel(int curr) {
    if (playerID == 0) {        // Alice
        scene->updateLevel(1.0 - (float)curr / (float)MAX_INSECURE);
    }
    else {                      // Others
        scene->updateLevel((float)curr / (float)MAX_INSECURE);
    }
}

void Window::updateTime(int curr) {
    scene->updateTime(curr);
}

void Window::setUiByPlayerID() {
    scene->setUiByPlayerID(playerID);
}
void Window::updateButtons(std::vector<int> buttonAssignment) {
    //std::cout << playerID << std::endl;
    toReady = true;
    for (int i = 0; i < buttonAssignment.size(); i++)
    {
        int buttonNum = buttonAssignment[i];
        if (buttonNum < 0 || buttonNum > 3) toReady = false;

        switch (buttonNum)
        {
        case 0:
            //scene->updateCharBtn(0, "./resources/images/test2.png");
            scene->a_state = 1;
            break;
        case 1:
            //scene->updateCharBtn(1, "./resources/images/test2.png");
            scene->b_state = 1;
            break;
        case 2:
            //scene->updateCharBtn(2, "./resources/images/test2.png");
            scene->c_state = 1;
            break;
        case 3:
            //scene->updateCharBtn(3, "./resources/images/test2.png");
            scene->d_state = 1;
            break;
        default:
            break;
        }

        if (i == playerID && buttonAssignment[i] >= 0) {
            if (buttonAssignment[i] == 0) scene->a_state = 2;
            if (buttonAssignment[i] == 1) scene->b_state = 2;
            if (buttonAssignment[i] == 2) scene->c_state = 2;
            if (buttonAssignment[i] == 3) scene->d_state = 2;
            //    scene->updateCharBtn(buttonNum, "./resources/images/testX.png");
        }
    }
    if (toReady) scene->ready_state = 1;//scene->updateReadyBtn("./resources/images/test.png");
}

void Window::updateBySkill(GameData* gd) {
    if (gd->player_status[0] == (int)PlayerStatus::SKILL) {
        Window::scene->drawAliceParticle = true;
    }
    if (gd->player_status[1] == (int)PlayerStatus::SKILL) {
        // TODO:: place sign/label at locB
        Window::scene->setSignModel(gd->location_B);
        Window::scene->playersObjects.at(1)->doAction();
    }
    if (gd->player_status[2] == (int)PlayerStatus::SKILL) {
        Window::scene->lights->updateSkillLight(gd->location_C);
        Window::scene->playersObjects.at(2)->doAction();
        // TODO:: place light at locC  
    }

    if (gd->skill_cd[3] >= 20000) {
        Window::scene->drawDaveSkill = true;
    }
    else {
        Window::scene->drawDaveSkill = false;

    }
    if (gd->player_status[playerID] == (int)PlayerStatus::ATTACK)
    {
        Window::scene->playersObjects.at(playerID)->doAttack();
    }
}