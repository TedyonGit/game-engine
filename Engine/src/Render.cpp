#include <Render.h>

RenderClass Render;

void RenderClass::Update()
{
    Interface.viewport->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto &obj : mapObjects)
    {
        obj.second->Update();
    }
    Interface.viewport->Unbind();
}

void RenderClass::Add(std::string Key, ObjectClass* value)
{
    mapObjects.insert({Key, value});
}

void RenderClass::Init()
{
    for(auto &obj : mapObjects)
    {
        obj.second->Init();
    }
    //  float vertices[] = {
    //     -0.2f, 0.2f, 0.0f,
    //      0.2f, 0.2f, 0.0f,
    //      0.2f, -0.2f, 0.0f,
    //      -0.2f, -0.2f, 0.0f,
    // };

    // unsigned int indices[] = {
    //     0, 1, 2,
    //     2, 3, 0
    // };
    // vb = new VertexBuffer(vertices, sizeof(vertices));
    // ib = new IndexBuffer(indices, 6);
    // va = new VertexArray();
    // va->AddBuffer(*vb, 0, 3, 3 * sizeof(float), 0);

    // shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    // shader->Bind();
    // va->Bind();
    // ib->Bind();
    // shader->SetVec3("Color", glm::vec3(1.0f, 1.0f, 1.0f));
}