#include <Interface.h>

InterfaceClass Interface;
UILayout Layout;

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
    Interface.Windows["Output"] = []() { Interface.Output(); };
    Interface.Windows["Scene"] = []() { Interface.Scene(); };
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
    glfwGetWindowSize(Interface.Window, w, h);
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
            ImGui::BeginDisabled(true);
            if (ImGui::MenuItem("Save", "Ctrl+S")) 
            {

            }
            ImGui::EndDisabled();
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

void InterfaceClass::Output()
{
    ImGui::SetNextWindowPos (Layout.Pos(0.0f, 0.75f));
    ImGui::SetNextWindowSize(Layout.Size(1.f, 0.25f));
    ImGui::Begin("Output", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    {
        ImGui::Text("Nothing to show...");
    }
    ImGui::End();
}

void InterfaceClass::Scene()
{
    ImGui::SetNextWindowPos (Layout.Pos(0.201f, 0.025f));
    ImGui::SetNextWindowSize(Layout.Size(0.599f, 0.72f));
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    {
    }
    ImGui::End();
}

void InterfaceClass::FileManager()
{
    ImGui::SetNextWindowPos(Layout.Pos(0.0f, 0.025f));
    ImGui::SetNextWindowSize(Layout.Size(0.20f, 0.72f));
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::End();
}

void InterfaceClass::Assets()
{
    ImGui::SetNextWindowPos(Layout.Pos(0.80f, 0.025f));
    ImGui::SetNextWindowSize(Layout.Size(0.20f, 0.72f));
    ImGui::Begin("Assets", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::End();
}


void InterfaceClass::Update()
{
    Layout.Update();
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