#pragma once

#include <vector>
#include "data/Vertex.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int vaoID;

	void Load();
	//std::vector<uint16_t> indices;
};