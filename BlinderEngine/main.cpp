#include "Window.h"
#include "core.h"
#include "../shared/Player.h"
#include <chrono>
#include <ctime>
#include "include/Audio.h"
#include <thread>

void error_callback(int error, const char* description) {
    // Print error.
    std::cerr << description << std::endl;
}

void setup_callbacks(GLFWwindow* window) {
    // Set the error callback.
    glfwSetErrorCallback(error_callback);
    // Set the window resize callback.
    glfwSetWindowSizeCallback(window, Window::resizeCallback);

    // Set the key callback.
    glfwSetKeyCallback(window, Window::keyCallback);

    // Set the mouse and cursor callbacks
    glfwSetMouseButtonCallback(window, Window::mouse_callback);
    glfwSetCursorPosCallback(window, Window::cursor_callback);
}

void setup_opengl_settings() {
    // Enable depth buffering.
    glEnable(GL_DEPTH_TEST);
    // Related to shaders and z value comparisons for the depth buffer.
    glDepthFunc(GL_LEQUAL);
    // Set polygon drawing mode to fill front and back of each polygon.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Set clear color to black.
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void print_versions() {
    // Get info of GPU and supported OpenGL version.
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version supported: " << glGetString(GL_VERSION)
              << std::endl;

    // If the shading language symbol is defined.
#ifdef GL_SHADING_LANGUAGE_VERSION
    std::cout << "Supported GLSL version is: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif
}

void loadSceneObject() {
    if (!Window::scene->loadingModel) {
        std::cout << "loading models" << std::endl;
        Window::scene->loadingModel = true;
        Window::scene->loadGameObjects();
    }
}

int main(void) {
    std::cout << "entrypoint" << std::endl;
    GLFWwindow* window = Window::createWindow(800, 600);
    if (!window) exit(EXIT_FAILURE);

    // Print OpenGL and GLSL versions.
    print_versions();
    // Setup callbacks.
    setup_callbacks(window);
    // Setup OpenGL settings.
    setup_opengl_settings();

    // Initialize the shader program; exit if initialization fails.

    if (!Window::initializeProgram()) exit(EXIT_FAILURE);
    

    // TODO(graphics): load landing page

    // Client setup
    Client* cli = new Client();
    int client_id = -1; // where to find corresponding character id
    if (!Constants::offline)
    {
        client_id = cli->accept_init();
        while (client_id == -1 && !Constants::offline) {
            client_id = cli->accept_init();

        }
    }

    Window::initializeCover();
    Window::initializeLanding();
    Window::initializeInstruction();

    while (!glfwWindowShouldClose(window))
    {
        cli->initialize_data();
        Window::playerID = client_id;
        
        // Cover
        Window::displayCoverPage(window);

        while (!Window::clickRestart) {
            Window::displayCoverPage(window);
        }

        // Instruction
        Window::clickRestart = false;
        Window::displayInstructionPage(window);

        while (!Window::clickRestart) {
            Window::displayInstructionPage(window);
        }

        // listen for initial game data
        int check_gd = cli->recv_gamedata();
        while (check_gd == -1 && !Constants::offline) {
            check_gd = cli->recv_gamedata();
        }

        // load landing&character selection page
        if (!Constants::offline) {
            Window::state = WindowState::LANDING;
            Window::scene->initLandingPage();
            Window::toReady = false;

            Window::drawLanding(window);

            while (Window::state == WindowState::LANDING) {
                Window::drawLanding(window);
                if (Window::acq_char_id != -1
                    && cli->buttonAssignment[client_id] == -1
                    && cli->button_available(Window::acq_char_id)) {
                    cli->acq_character(Window::acq_char_id);
                    std::cout << "sending acq..." << std::endl;
                    Window::acq_char_id = -1;
                }
                if (cli->recv_buttonAssignment() != -1) {
                    Window::updateButtons(cli->buttonAssignment);
                }
            }
        }
    

        std::cout << "sending ready" << std::endl;
        // TODO: check user action(ready for game) & send event packet
        cli->send_event(EventType::READY);
        // listen for init packet

        int assigned_id;
        if (Constants::offline) {
            assigned_id = 3;
        }
        else {
            assigned_id = cli->buttonAssignment[client_id];
        }
        Window::playerID = assigned_id;
        // render things based on assigned_id & player setup
        Player* player = new Player(assigned_id);
        player->setCharacter((Character)assigned_id);


        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        // Initialize objects/pointers for rendering; exit if initialization fails.
        if (!Window::initializeObjects(assigned_id)) exit(EXIT_FAILURE);
        Window::scene->setUiByPlayerID(assigned_id);

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

        // listen for game start
        int check_start = cli->recv_gamedata();
        while (check_start == -1 && !Constants::offline) {
            check_start = cli->recv_gamedata();
        }

        Audio::init(assigned_id);
        Audio::playBgm();

        // Loop while GLFW window should stay open.
        while (!glfwWindowShouldClose(window)) {

            // check for event&send

            if (!Window::no_event)
            {
                cli->send_eventRecords(Window::eventChecker);
            }

            // listen for updated game data
            check_gd = cli->recv_gamedata();


            // TODO(graphics): update graphics based on cli->gd
            if (Constants::offline) {
                /*glm::mat4 mat = {
                    1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    10,5,1,1
                };*/
                //Window::scene->setSignModel(mat);
            }
            else if (check_gd != -1) {
                Window::scene->playersObjects.at(0)->setModel(cli->gd->location_A);
                Window::scene->playersObjects.at(1)->setModel(cli->gd->location_B);
                Window::scene->playersObjects.at(2)->setModel(cli->gd->location_C);
                Window::scene->playersObjects.at(3)->setModel(cli->gd->location_D);
                player->updateByGD(cli->gd);
                Window::updateLevel(player->getLevel());
                Window::updateTime(cli->gd->remaining_time);
                Window::updateBySkill(cli->gd);
                Window::updateByWalk(cli->gd);
            }
            Window::no_event = true;
            std::fill(Window::eventChecker.begin(), Window::eventChecker.end(), 0);// avoid double action
            // Idle callback. Updating objects, etc. can be done here.
            /*int key = 0;
            int scancode = 0;
            int action = 0; 
            int mods=0;
            Window::keyCallback(window, key,  scancode,  action, mods);*/
            Window::idleCallback();
            if (player->getLevel() >= AWARENESS_THRESHOLD) {
                Window::scene->ui->setPlayerAlicePosition(Window::scene->playersObjects[0]->getModel());
            }
            // Main render display callback. Rendering of objects is done here.
            if (Constants::offline) {
                /*float rate;
                cin >> rate;
                Window::ui->changeLevelbarSizeY(rate);
                Window::ui->changeTimebarSizeY(rate);*/

                if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                    Audio::playskill(Window::getPos());

                }
                Window::displayCallback(window, std::vector<int>(NUM_OBSTACLE, 2), SKILL_CD);
            }
            else {
                Window::displayCallback(window, cli->gd->obstacle_states, cli->gd->skill_cd.at(Window::playerID));
                Audio::playHpLow(cli->gd);
                Audio::playSkillAudio(cli->gd, Window::scene->map->obs->cubes);
                // check game end logic
                if (cli->gd->gamestate == GameState::LOSE ||
                    cli->gd->gamestate == GameState::WIN) {
                    std::chrono::time_point<std::chrono::system_clock> start_, end_;
                    std::chrono::duration<double> elapsed_seconds_;
                    start_ = std::chrono::system_clock::now();
                    while (elapsed_seconds_.count() < 2) {
                        end_ = std::chrono::system_clock::now();
                        elapsed_seconds_ = end_ - start_;
                    }
                    std::cout << "elapsed time: " << elapsed_seconds_.count() << "s\n";
                    break;
                }
            }
        }
        if (!Constants::offline) {
            Window::setEndPage(cli->gd->gamestate);
            Audio::playEnd(cli->gd->gamestate);
        }
        bool check_send_restart = false;
        while (!glfwWindowShouldClose(window)) {
            Window::displayEndPage(window);
            if (Window::clickRestart && !check_send_restart) {
                cli->send_event(EventType::RESTART);
                Window::clickRestart = false;
                check_send_restart = true;
                std::cout << " send restart" << std::endl;
            }
            cli->recv_gamedata();
            if (cli->gd->gamestate == GameState::READY) {
                break;
            }
        }
    }

    Window::cleanUp();
    // Destroy the window.
    glfwDestroyWindow(window);
    // Terminate GLFW.
    glfwTerminate();

    Audio::deinit();
    exit(EXIT_SUCCESS);
}

