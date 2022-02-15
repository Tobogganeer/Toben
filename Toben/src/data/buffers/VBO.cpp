#include "Buffers.h"
#include "../../graphics/Graphics.h"

VBO::VBO(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VBO::~VBO()
{
    GLCall(glDeleteBuffers(1, &ID));
}


void VBO::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void VBO::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}