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
    ImVec2 SceneSize = Layout.Size(0.599f, 0.72f);
    Interface.viewport = new Framebuffer(SceneSize.x, SceneSize.y);
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
        if(Logs.empty())
            ImGui::Text("Nothing to show...");
        else
        {
            for(auto& d : Logs)
            {
                ImGui::Text(d.c_str());
            }
        }
    }
    ImGui::End();
}

void InterfaceClass::Scene()
{
    ImVec2 pos, size;
    pos = Layout.Pos(0.201f, 0.025f);
    size = Layout.Size(0.599f, 0.72f);

    viewport->Width = size.x;
    viewport->Height = size.y;
    
    ImGui::SetNextWindowPos (pos);
    ImGui::SetNextWindowSize(size);
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    {
        Interface.SceneSelected = ImGui::IsWindowFocused();        
        ImVec2 size = ImGui::GetContentRegionAvail();
        Interface.viewport->Resize((int)size.x, (int)size.y);
        ImGui::Image((ImTextureID)(intptr_t)viewport->TextureID, size);
    }
    ImGui::End();
}

void InterfaceClass::FileManager()
{
    ImGui::SetNextWindowPos(Layout.Pos(0.0f, 0.025f));
    ImGui::SetNextWindowSize(Layout.Size(0.20f, 0.72f));
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    if(ImGui::Button("Add"))
    {
        std::string Name = "Object ";
        Name.append(std::to_string(Render.mapObjects.size() + 1));
        ObjectClass* Obj = new ObjectClass(Interface.viewport);
        Obj->Position.y += 0.42f * Render.mapObjects.size(); 
        Obj->Init();
        Render.Add(Name, Obj);
        Name.append(" added to the file manager.");
        Logs.push_back(Name);
    }
    std::string toDelete = "";

    for (auto& obj : Render.mapObjects)
    {
        ImGui::BeginGroup();
        ImGui::Text(obj.first.c_str());
        ImGui::SameLine();
        if (ImGui::Button(("Delete##" + obj.first).c_str()))
            toDelete = obj.first;
        ImGui::EndGroup();
    }
    if (!toDelete.empty())
    {
        Render.mapObjects[toDelete]->Delete();
        Render.mapObjects.erase(toDelete);
        toDelete.append(" deleted from the file manager.");
        Logs.push_back(toDelete);
    }
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