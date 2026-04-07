#include <Window.h>

WindowClass Window;

int WindowClass::Create()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    windowobj = glfwCreateWindow(mode->width, mode->height, "Game Engine", nullptr, nullptr);
    
    if (!windowobj)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(windowobj, WindowClass::WndProc);
    glfwMakeContextCurrent(windowobj);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU: "   << glGetString(GL_RENDERER) << "\n";
    return 0;
}

void WindowClass::WndProc(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if(!window || window == nullptr)
        return;

    switch (key) {
        case 'W': case 'A': case 'S': case 'D': Camera.Move(key, Window.DeltaTime, Interface.SceneSelected); break;
        default: break;
    }
}

int WindowClass::Update()
{
    while (!glfwWindowShouldClose(windowobj))
    {
        glfwPollEvents();
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        glfwSwapBuffers(windowobj);
    }

    glfwTerminate();
    return 0;
}

bool WindowClass::ShouldRun() const
{
    return !glfwWindowShouldClose(windowobj);
}

void WindowClass::BeginFrame()
{
    float currentFrame = (float)glfwGetTime();
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void WindowClass::EndFrame()
{
    glfwSwapBuffers(windowobj);
}