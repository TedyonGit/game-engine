#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <Interface.h>

class WindowClass
{
    public:
        int Create();
        int Update();
        bool ShouldRun()  const;
        void BeginFrame();
        void EndFrame();
        GLFWwindow* windowobj = nullptr;
    
        float DeltaTime  = 0.0f;
        float LastFrame  = 0.0f;
        static void WndProc(GLFWwindow* window, int key, int scancode, int action, int mods);
};

extern WindowClass Window;