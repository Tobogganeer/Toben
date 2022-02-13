#include "Buffers.h"
#include "../../graphics/Graphics.h"

IBO::IBO() {}

IBO::IBO(const unsigned int* data, unsigned int count)
    : count(count)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IBO::~IBO()
{
    glDeleteBuffers(1, &ID);
}


void IBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IBO::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}