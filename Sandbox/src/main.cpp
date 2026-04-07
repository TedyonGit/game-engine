#include <Window.h>
#include <glm/glm.hpp>
#include <Interface.h>
#include <Render.h>

int main()
{
    if (Window.Create() != 0)
        return -1;
    Render.Init();
    Interface.Init(Window.windowobj);
   

    while (Window.ShouldRun())
    {
        Window.BeginFrame();
        {
            Render.Update();
            Interface.Update();
        }

        Window.EndFrame();
    }
    Interface.CleanUp();
    return 0;
}