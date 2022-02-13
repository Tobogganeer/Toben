#pragma once

#include <vector>
#include "Vertex.h"
#include "buffers/Buffers.h"
#include "../utils/HeapData.h"

class Mesh
{
public:
	HeapRef<std::vector<Vertex>> vertices;
	HeapRef<std::vector<unsigned int>> indices;

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void Load();
	void Unload();
	~Mesh();
	//std::vector<uint16_t> indices;

private:
	VAO vao;
	VBO vbo;
	IBO ibo;
};