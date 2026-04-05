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

    // Attach a vertex buffer and describe its layout
    // stride = total size of one vertex in bytes
    // offset = where this attribute starts in the vertex
    void AddBuffer(const VertexBuffer& vb,
                   unsigned int attribIndex,
                   int count,
                   unsigned int stride,
                   unsigned int offset);
};