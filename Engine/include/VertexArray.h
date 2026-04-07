#pragma once
#include <glad/glad.h>
#include <Buffer.h>

class VertexArray
{
public:
    unsigned int ID;

    VertexArray();
    ~VertexArray();

    void Bind()   const;
    void Unbind() const;

    void AddBuffer(const VertexBuffer& vb, unsigned int attribIndex, int count, unsigned int stride, unsigned int offset);
};