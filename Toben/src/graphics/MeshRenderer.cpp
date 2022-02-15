#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const HeapRef<Mesh> mesh, const HeapRef<Material> material)
	:mesh(mesh), material(material) {}