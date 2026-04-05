#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowClass
{
public:
    int Create();
    int Update();
    bool ShouldRun()  const;
    void BeginFrame();
    void EndFrame();
    GLFWwindow* windowobj = nullptr;
};

extern WindowClass Window;