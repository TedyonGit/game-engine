#include <VertexArray.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind()   const { glBindVertexArray(ID); }
void VertexArray::Unbind() const { glBindVertexArray(0);  }

void VertexArray::AddBuffer(const VertexBuffer& vb,
                             unsigned int attribIndex,
                             int count,
                             unsigned int stride,
                             unsigned int offset)
{
    Bind();
    vb.Bind();
    glVertexAttribPointer(attribIndex, count, GL_FLOAT, GL_FALSE,
                          stride, (void*)(uintptr_t)offset);
    glEnableVertexAttribArray(attribIndex);
}