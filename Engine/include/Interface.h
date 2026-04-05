#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class InterfaceClass
{
    public:
        int Init(GLFWwindow* Window);
        int CreateWindow();
        int DeleteWindow();
        void Update();
        void CleanUp();
    private:
        void Test();
        GLFWwindow* Window = nullptr;
        std::unordered_map<std::string, std::function<void()>> Windows;
};

extern InterfaceClass Interface;