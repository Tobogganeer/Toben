#include "Buffers.h"
#include "../../graphics/Graphics.h"

VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &ID));
	GLCall(glBindVertexArray(ID));
}
VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &ID));
}


void VAO::Add(const HeapRef<VBO> vbo, const BufferLayout& layout)
{
	Bind();
	vbo->Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * BufferElement::GetSize(element.type);
	}
}

void VAO::Bind() const
{
	GLCall(glBindVertexArray(ID));
}
void VAO::Unbind() const
{
	GLCall(glBindVertexArray(0));
}