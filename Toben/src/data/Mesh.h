#pragma once

#include "Vertex.h"
#include "buffers/Buffers.h"
#include "../utils/HeapData.h"

#include <vector>

class Mesh
{
public:
	HeapRef<std::vector<Vertex>> vertices;
	HeapRef<std::vector<unsigned int>> indices;

	Mesh(HeapRef<std::vector<Vertex>> vertices, HeapRef<std::vector<unsigned int>> indices);
	void Load();
	void Unload();
	~Mesh();

	static HeapRef<Mesh> Create(HeapRef<std::vector<Vertex>> vertices, HeapRef<std::vector<unsigned int>> indices);

private:
	HeapRef<VAO> vao;
	HeapRef<VBO> vbo;
	HeapRef<IBO> ibo;
};