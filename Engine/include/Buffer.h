#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
    unsigned int ID;

    VertexBuffer(float* vertices, unsigned int size);
    ~VertexBuffer();

    void Bind()   const;
    void Unbind() const;
};

class IndexBuffer
{
public:
    unsigned int ID;
    unsigned int Count;

    IndexBuffer(unsigned int* indices, unsigned int count);
    ~IndexBuffer();

    void Bind()   const;
    void Unbind() const;
};