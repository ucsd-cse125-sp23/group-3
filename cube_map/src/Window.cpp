#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "Model Environment";

// Objects to render
Cube* Window::cube;
Map* Window::map;
Minimap* Window::canvas;
// Camera Properties
Camera* Cam;

// Interaction Variables
bool LeftDown, RightDown;
int MouseX, MouseY;
const float cameraSpeed = 1.0f;
const float turningratio=30.0f;

bool usingSkill;
float skillTime = 1.0f;
double timer=0.0f;

// The shader program id
GLuint Window::shaderProgram;
Shader* Window::shaderText2DProgram;
CollisionDetection collisionDetection;
Mult_Lights* Window::lights;
Particles* Window::particles;
Particles* particles_2;
AliceSkill* skill;
struct Particle* leading=new Particle();
bool onMOVE;
// Constructors and desctructors
bool Window::initializeProgram() {
    

    // Create a shader program with a vertex shader and a fragment shader.
    shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    //lights.loadToUShader(shaderProgram,Camera);
    //std::cout<<"make myself here"<<std::endl;
    shaderText2DProgram=new Shader("shaders/particles.vs", "shaders/particles.fs"); 
    // Check the shader program.
    if (!shaderProgram) {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }

    return true;
}

bool Window::initializeObjects() {
    lights=new Mult_Lights(true);
    
    // Create a cube
    cube = new Cube();
    map=new Map();
    //particles=new Particles(1000,false);
    lights->AddLightBCD(map->calculateBCDLightcenter());

    //EVERTHING NEED FOR SETUP A PARTICLE SYSTEM
    /*
    particles_2=new Particles(1000,true,5.0f,0.1f,0.8f,glm::vec3(0.8f,0.8f,1.0f));
    particles_2->bindTexture("./images/particle.png");
    
    
    lights->particles_light.push_back(particles_2->light);
    leading->Position=glm::vec3(3.0f,3.0f,0.0f);
    leading->Velocity=glm::vec3(0.1f,0.0f,0.1f)*5.0f;*/

    skill=new AliceSkill(lights->particles_light);

    /*std::cout<<particles_2->light->diffuse<<std::endl;
    std::cout<<particles_2->light->ambient<<std::endl;
    std::cout<<particles_2->light->specular<<std::endl;*/
    glm::mat4 somerot=glm::mat4(1.0f);
    somerot=somerot*glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setModel(map->getModelOnMap(somerot,2,0.5,4.5));
    Cam->setModel(map->getModelOnMap(somerot,2,0.5,4.5));
    // cube = new Cube(glm::vec3(-1, 0, -2), glm::vec3(1, 1, 1));
    //canvas=new Minimap(0.4,(800*(0.4*sqrt(3))/2)/600,-0.0,-1.0);
    return true;
}

void Window::cleanUp() {
    // Deallcoate the objects.
    delete cube;
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
    Cam->Update();
    map->update();
    //std::cout<<"error here"<<std::endl;
    lights->updateLightAlice(map->calculateLightcenter(cube->getModel()),onMOVE);
    //std::cout<<"error here"<<std::endl;

    double newtimer=glfwGetTime();
    float dt=(newtimer-timer);
    //std::cout<<dt<<std::endl;
    timer=newtimer;
    //std::cout<<"error here"<<std::endl;

    

    //std::cout<<"error here"<<std::endl;
    //particles->Update(dt,leading->Velocity,leading->Position,3,glm::vec3(0.0f));

    //particles_2->Update(dt,leading->Velocity,leading->Position,3,glm::vec3(0.0f));

    //particles_2->Update(dt,glm::vec3(0.0f),glm::vec3(1.0f),3,glm::vec3(0.0f));
    //std::cout<<"error here"<<std::endl;

    

    /*std::cout<<particles_2->light->diffuse<<std::endl;
    std::cout<<particles_2->light->ambient<<std::endl;
    std::cout<<particles_2->light->specular<<std::endl;*/
    //particles->Update(dt,glm::vec3(1.0f),glm::vec3(1.0f),3,glm::vec3(0.0f));
    //std::cout<<"error here"<<std::endl;
    //lights->updateLightAliceV2(cube->getModel());

    if (usingSkill && skillTime > 0) {
        
        skillTime -= 0.0003f;
        skill->SetUp(cube->getModel());
        //leading->Position+=leading->Velocity*dt;
        //UPDATION FOR SYSTEM +LIGHT AT END
        /*leading->Position+=leading->Velocity*dt;
        particles_2->Update(dt,leading->Velocity,leading->Position,1,glm::vec3(0.0f));*/
        //lights->particles_light[0]=particles_2->light;
        // lights->particles_light[0]=particles_2->light;
    } else {
        skillTime = 1.0f;
        skill->start=false;
        skill->setup=false;
        usingSkill = false;
        /*particles_2->Update(dt,leading->Velocity,leading->Position,0,glm::vec3(0.0f));
        usingSkill = false;
        skillTime = 1.0f;*/
        
    }
    skill->update(dt);
    //lights->particles_light[0]=particles_2->light;
    //lights->update(Cam);
    //cube->update();
}

void Window::displayCallback(GLFWwindow* window) {
    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //std::cout<<"error here"<<std::endl;
    lights->loadToUShader(shaderProgram,*Cam);
    // Render the object.
    cube->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    //ground->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    map->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    //std::cout<<"make myself here"<<std::endl;
    //canvas->draw(glm::mat4 (1.0f), *shaderText2DProgram);
    //particles->Draw(*(Window::shaderText2DProgram), Cam->GetViewProjectMtx());
   // std::cout<<"error here"<<std::endl;
    //particles_2->Draw(*(Window::shaderText2DProgram), Cam->GetViewProjectMtx(),Cam->Projection);
    skill->draw(*(Window::shaderText2DProgram), Cam->GetViewProjectMtx(),Cam->Projection);
    //std::cout<<"error here"<<std::endl;
    //std::cout<<"error here"<<std::endl;
    int mapID;
    float x,y;
    map->getPosition(cube->getModel(),&mapID,&y,&x);

    std::vector<std::pair<float, float>> points = map->getGrid(mapID,x,y);
    if (collisionDetection.checkCollisionWithWall(mapID, points)) {
        // std::cout<<"colliding!"<<std::endl;
        Cam->SetMove(cameraSpeed);
        cube->move(cameraSpeed);
    }
    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

// helper to reset the camera
void Window::resetCamera() {
    Cam->Reset();
    Cam->SetAspect(float(Window::width) / float(Window::height));
}
// callbacks - for Interaction
void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*
     * TODO: Modify below to add your key callbacks.
     */
    onMOVE=false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Cam->SetMove(-cameraSpeed);
        cube->move(-cameraSpeed);
        onMOVE=true;
    }
        
    /*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        Cam->SetMove(cameraSpeed);
        cube->move(cameraSpeed);
    }*/
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Cam->SetSpin(cameraSpeed*turningratio);
        cube->spin(cameraSpeed*turningratio);
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        Cam->SetSpin(-cameraSpeed*turningratio);
        cube->spin(-cameraSpeed*turningratio);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        // eventChecker[(int)EventType::ATTACK - 1] = 1;
        if (skillTime == 1.0f) {
            usingSkill = true;
            //leading->Position=glm::vec3(3.0f,3.0f,0.0f);
        }
        // no_event = false;
    }

    // Check for a key press.
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;

            case GLFW_KEY_R:
                resetCamera();
                break;

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



