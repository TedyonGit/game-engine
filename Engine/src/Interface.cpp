#include <Interface.h>

InterfaceClass Interface;

int InterfaceClass::Init(GLFWwindow* Window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
    ImGui::GetIO().IniFilename = nullptr;
	ImGui::GetIO().LogFilename = nullptr;
    Interface.Window = Window;
    Interface.Windows["File Manager"] = []() { Interface.FileManager(); };
    Interface.Windows["Menu Bar"] = []() { Interface.MenuBar(); };
    Interface.Windows["Assets"] = []() { Interface.Assets(); };
    return 1;
}


void InterfaceClass::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void InterfaceClass::GetWindowSize(int* w, int* h)
{
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    *w = mode->width;
    *h = mode->height;
}

void InterfaceClass::MenuBar()
{
    if (ImGui::BeginMainMenuBar()) 
    {
        if (ImGui::BeginMenu("File")) 
        {
            if (ImGui::MenuItem("New")) 
            { 

            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) 
            { 

            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) 
            {

            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Interface")) 
        {
            for(auto& i : Interface.Windows)
            {
                if(!i.first.find("Menu Bar"))
                    continue;
                if (ImGui::MenuItem(i.first.c_str(), i.second != nullptr ? "X" : "")) 
                { 
                    if(i.second != nullptr)
                    {
                        Interface.HiddenWindows[i.first] =  i.second;
                        i.second = nullptr;
                    } else 
                    {
                        i.second = Interface.HiddenWindows[i.first];
                        Interface.HiddenWindows.erase(i.first);
                    }
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void InterfaceClass::FileManager()
{
    int w = 0, h = 0;
    Interface.GetWindowSize(&w, &h);
    ImGui::SetNextWindowPos({0, 25});
    ImGui::SetNextWindowSize({430, (float)h});
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::End();
}

void InterfaceClass::Assets()
{
    int w = 0, h = 0;
    Interface.GetWindowSize(&w, &h);
    ImGui::SetNextWindowPos({w - 430, 25});
    ImGui::SetNextWindowSize({430, (float)h});
    ImGui::Begin("Assets", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::End();
}


void InterfaceClass::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    for(auto& Window : Interface.Windows)
    {
        if(Window.second != nullptr)
            Window.second();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}