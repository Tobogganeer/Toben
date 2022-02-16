#pragma once

#include <GL/glew.h>
#include "BufferLayout.h"
#include "../../utils/HeapData.h"
//#include "../../graphics/Graphics.h"

class VBO
{
private:
	unsigned int ID;

public:
	VBO() = default;
	VBO(const void* data, unsigned int size);
	~VBO();

	void Bind() const;
	void Unbind() const;
};

class IBO
{
private:
	unsigned int ID;
	unsigned int count;
public:
	
	IBO(const unsigned int* data, unsigned int count);
	~IBO();
	IBO();

	void Bind() const;
	void Unbind() const;
};

class VAO
{
private:
	unsigned int ID;

public:
	VAO();
	~VAO();

	void Add(const HeapRef<VBO> vbo, const BufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};