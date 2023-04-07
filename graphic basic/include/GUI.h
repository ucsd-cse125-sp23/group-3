#pragma once

#include "Camera.h"
#include "Skeleton.h"
#include "Shader.h"
#include "Joint.h"
#include "Window.h"
#include "DOF.h"
#include <vector>
#include "core.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> 

class GUI{
    public:
        static bool show_timer_window;
        static int ctr;
        static void setGUI(GLFWwindow* window2);
        static void getDOF(GLFWwindow* window2);
        static void shutdown(GLFWwindow* window2);
};