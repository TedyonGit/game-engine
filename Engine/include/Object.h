#pragma once
#include <Shader.h>
#include <Buffer.h>
#include <VertexArray.h>
#include <Camera.h>
#include <FrameBuffer.h>
#include <Render.h>

class ObjectClass
{
    public:
        ObjectClass(Framebuffer* temp)
        {
            viewport = temp;
        }
        void Delete()
        {
            delete shader;
            delete va;
            delete vb;
            delete ib;

            shader = nullptr;
            va     = nullptr;
            vb     = nullptr;
            ib     = nullptr;
        }
        void Init()
        {
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
            vb = new VertexBuffer(vertices, sizeof(vertices));
            ib = new IndexBuffer(indices, 6);
            va = new VertexArray();
            va->AddBuffer(*vb, 0, 3, 3 * sizeof(float), 0);

            shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
            shader->Bind();
            va->Bind();
            ib->Bind();
            shader->SetVec3("Color", Color);
        }
        void Update()
        {
            shader->Bind();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, Position);
            shader->SetMat4("Model", model);
            shader->SetMat4("View",       Camera.GetView());
            float aspect = (viewport->Height > 0)
                ? (float)viewport->Width / viewport->Height
                : 1280.0f / 720.0f;

            shader->SetMat4("Projection", Camera.GetProjection(aspect));

            //viewport->Bind();
                //
            glDrawElements(GL_TRIANGLES, ib->Count, GL_UNSIGNED_INT, nullptr);
            //viewport->Unbind();
        }
    glm::vec3 Position = { -1.4f, -0.8f, 0.0f };
    glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
    private:
        VertexBuffer* vb;
        IndexBuffer* ib;
        VertexArray* va;
        Shader* shader;
        Framebuffer* viewport;
        // Other stats
};