#include "GUI.h"
bool GUI::show_timer_window=false;
int GUI::ctr=0;

void GUI::setGUI(GLFWwindow* window2){
    if (window2 == NULL)
        return ;
    glfwMakeContextCurrent(window2);
    glfwSwapInterval(1); 
    const char* glsl_version = "#version 150";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window2, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Our state
    
}

void GUI::getDOF(GLFWwindow* window2){

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        //glfwPollEvents();

        // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    std:: vector<Joint*> jntlist= Joint::getList();

    ImGui::Begin("Adjust time");                          // Create a window called "Hello, world!" and append into it.

    /* for(std:: vector<Joint*>::iterator it = jntlist.begin(); it != jntlist.end(); it++){
        std::string namejnt=(*it)->getname();
        DOF* dofs=(*it)->getDOF();
        glm::vec3 value=dofs->GetValue();
        float x=value.x;
        float y=value.y;
        float z=value.z;
        bool isChangedx = false;
        bool isChangedy = false;
        bool isChangedz = false;
        ImGui::Text("name: %s",namejnt.c_str());               

        x, isChangedx=ImGui::SliderFloat((namejnt+"x").c_str(), &x, -3.14f, 3.14f,"%.3f",1); 
        y, isChangedy=ImGui::SliderFloat((namejnt+"y").c_str(), &y, -3.14f, 3.14f,"%.3f",1); 
        z, isChangedz= ImGui::SliderFloat((namejnt+"z").c_str(), &z, -3.14f, 3.14f,"%.3f",1);   
        if(isChangedx||isChangedy||isChangedz){
            dofs->SetValue(glm::vec3(x,y,z));
        }
    } */


    
    bool isChangedx = false;
    
    float newval;
    ImGui::Checkbox("Stop or Start", &show_timer_window); 
    if(show_timer_window){
        Window::stop=true;
        newval, isChangedx=ImGui::SliderFloat("timer adjustment", & (Window::currentFrame), -2, 12,"%.3f",1); 
    }
    else{
        Window::stop=false;
    }

    if(isChangedx){
        //std::cout<<(Window::currentFrame)<<std::endl;
        
    }
    

             // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::End();

    // Rendering
    //ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window2, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    //glClear(GL_COLOR_BUFFER_BIT);

    //glfwSwapBuffers(window2);
}

void GUI::shutdown(GLFWwindow* window2){
    if (window2 == NULL)
        return ;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}