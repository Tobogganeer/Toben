#pragma once

#include "../data/Mesh.h"
#include "../data/Material.h"
#include <vector>

class MeshRenderer
{
public:
	Mesh mesh;
	Material material;
	MeshRenderer(Mesh& mesh, Material& material);
};

