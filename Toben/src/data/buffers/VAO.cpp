#include "Buffers.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}
VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}


void VAO::Add(const VBO& vbo, const BufferLayout& layout)
{
	Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * BufferElement::GetSize(element.type);
	}
}

void VAO::Bind() const
{
	glBindVertexArray(ID);
}
void VAO::Unbind() const
{
	glBindVertexArray(0);
}