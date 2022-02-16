#pragma once

#include "../data/Mesh.h"
#include "../data/Material.h"
#include "../utils/HeapData.h"

class MeshRenderer
{
public:
	HeapRef<Mesh> mesh;
	HeapRef<Material> material;
	MeshRenderer(HeapRef<Mesh> mesh, HeapRef<Material> material);
	
	void Load() const;
	void Unload() const;
};

