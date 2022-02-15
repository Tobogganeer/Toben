#pragma once

#include <vector>
#include "Vertex.h"
#include "buffers/Buffers.h"
#include "../utils/HeapData.h"
#include "../graphics/Graphics.h"

class Mesh
{
public:
	HeapRef<std::vector<Vertex>> vertices;
	HeapRef<std::vector<unsigned int>> indices;

	Mesh(HeapRef<std::vector<Vertex>> vertices, HeapRef<std::vector<unsigned int>> indices);
	void Load();
	void Unload();
	~Mesh();
	//std::vector<uint16_t> indices;

private:
	HeapRef<VAO> vao;
	HeapRef<VBO> vbo;
	HeapRef<IBO> ibo;
};