#pragma once

#include "../data/Mesh.h"
#include "../data/Material.h"
#include "../utils/HeapData.h"

class MeshRenderer
{
public:
	HeapRef<Mesh> mesh;
	HeapRef<Material> material;
	MeshRenderer(const HeapRef<Mesh> mesh, const HeapRef<Material> material);
};

