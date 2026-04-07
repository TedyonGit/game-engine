#include <Window.h>
#include <Shader.h>
#include <Buffer.h>
#include <VertexArray.h>
#include <glm/glm.hpp>
#include <Interface.h>
#include <Camera.h>
#include <FrameBuffer.h>
int main()
{
    if (Window.Create() != 0)
        return -1;

    Interface.Init(Window.windowobj);
    float vertices[] = {
        -0.2f, 0.2f, 0.0f,
         0.2f, 0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
         -0.2f, -0.2f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, 6);
    VertexArray  va;

    va.AddBuffer(vb, 0, 3, 3 * sizeof(float), 0);

    Shader shader("assets/shaders/basic.vert",
                  "assets/shaders/basic.frag");
    shader.Bind();
    va.Bind();
    ib.Bind();
    shader.SetVec3("uColor", glm::vec3(1.0f, 1.0f, 0.0f));

    while (Window.ShouldRun())
    {
        Window.BeginFrame();
        {
            shader.Bind();
            shader.SetMat4("u_View",       Camera.GetView());
            float aspect = (Interface.viewport->Height > 0)
                ? (float)Interface.viewport->Width / Interface.viewport->Height
                : 1280.0f / 720.0f;

            shader.SetMat4("u_Projection", Camera.GetProjection(aspect));
            shader.SetMat4("u_Model",      glm::mat4(1.0f));

            Interface.viewport->Bind();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDrawElements(GL_TRIANGLES, ib.Count, GL_UNSIGNED_INT, nullptr);
            Interface.viewport->Unbind();

            Interface.Update();
        }

        Window.EndFrame();
    }
    Interface.CleanUp();
    return 0;
}