#include <Window.h>
#include <Shader.h>
#include <Buffer.h>
#include <VertexArray.h>
#include <glm/glm.hpp>
#include <Interface.h>

int main()
{
    if (Window.Create() != 0)
        return -1;

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    //      0.0f,  0.5f, 0.0f
    // };
    Interface.Init(Window.windowobj);
    float vertices[] = {
        -0.2f, 0.2f, 0.0f,
         0.2f, 0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
         -0.2f, -0.2f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,  // first triangle
        2, 3, 0   // second triangle
    };

    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, 6);
    VertexArray  va;

    // attribIndex=0, 3 floats, stride=3 floats, offset=0
    va.AddBuffer(vb, 0, 3, 3 * sizeof(float), 0);

    Shader shader("assets/shaders/basic.vert",
                  "assets/shaders/basic.frag");
    shader.Bind();
    va.Bind();
    ib.Bind();
    shader.SetVec3("uColor", glm::vec3(1.0f, 1.0f, 0.0f));

    // Pull the raw draw call out of Window and do it here
    while (Window.ShouldRun())
    {
        Window.BeginFrame();
        {

            // glDrawElements(GL_TRIANGLES, ib.Count, GL_UNSIGNED_INT, nullptr);
            
            Interface.Update();

        }

        Window.EndFrame();
    }
    Interface.CleanUp();
    return 0;
}