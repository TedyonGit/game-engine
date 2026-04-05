#include <Buffer.h>

// ── Vertex Buffer ────────────────────────────────────────────
VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::Bind()   const { glBindBuffer(GL_ARRAY_BUFFER, ID); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0);  }

// ── Index Buffer ─────────────────────────────────────────────
IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
    : Count(count)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::Bind()   const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  }