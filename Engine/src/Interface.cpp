#include <Interface.h>

InterfaceClass Interface;

int InterfaceClass::Init(GLFWwindow* Window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
    Interface.Window = Window;
    Interface.Windows["Test"] = []() { Interface.Test(); };
    return 1;
}


void InterfaceClass::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void InterfaceClass::Test()
{
    ImGui::Begin("Debug");
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::End();
}

void InterfaceClass::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    for(auto& Window : Interface.Windows)
    {
        Window.second();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}