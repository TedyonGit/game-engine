#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <FrameBuffer.h>
#include <GLFW/glfw3.h>
#include <Render.h>


class InterfaceClass
{
    public:
        int Init(GLFWwindow* Window);
        int CreateWindow();
        int DeleteWindow();
        void Update();
        void CleanUp();
        void GetWindowSize(int* w, int* h);
        Framebuffer* viewport;
        bool SceneSelected = false;
    private:
        void FileManager();
        void MenuBar();
        void Assets();
        void Output();
        void Scene();
        GLFWwindow* Window = nullptr;
        std::unordered_map<std::string, std::function<void()>> Windows;
        std::unordered_map<std::string, std::function<void()>> HiddenWindows;
        std::vector <std::string> Logs;
};
extern InterfaceClass Interface;

struct UILayout
{
    int w = 0, h = 0;

    void Update()
    {
        Interface.GetWindowSize(&w, &h);
    }

    float X(float ratio) { return w * ratio; }
    float Y(float ratio) { return h * ratio; }

    ImVec2 Pos(float xRatio, float yRatio)  { return { X(xRatio), Y(yRatio) }; }
    ImVec2 Size(float wRatio, float hRatio) { return { X(wRatio), Y(hRatio) }; }
};

extern UILayout Layout;