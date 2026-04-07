#include <Shader.h>
#include <Buffer.h>
#include <VertexArray.h>
#include <Interface.h>
#include <Camera.h>

class RenderClass
{
    public:
        void Update();
        void Init();
    private:
        VertexBuffer* vb;
        IndexBuffer* ib;
        VertexArray* va;
        Shader* shader;
};

extern RenderClass Render;