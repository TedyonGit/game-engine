#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class InterfaceClass
{
    public:
        int Init(GLFWwindow* Window);
        int CreateWindow();
        int DeleteWindow();
        void Update();
        void CleanUp();
        void GetWindowSize(int* w, int* h);
    private:
        void FileManager();
        void MenuBar();
        void Assets();
        void Output();
        GLFWwindow* Window = nullptr;
        std::unordered_map<std::string, std::function<void()>> Windows;
        std::unordered_map<std::string, std::function<void()>> HiddenWindows;
};

extern InterfaceClass Interface;