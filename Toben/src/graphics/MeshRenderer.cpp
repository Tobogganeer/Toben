#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const HeapRef<Mesh> mesh, const HeapRef<Material> material)
	:mesh(mesh), material(material) {}

void MeshRenderer::Load() const
{
	mesh->Load();
	material->LoadUniforms();
	material->shader.Bind();
	material->mainTexture.Bind();
}

void MeshRenderer::Unload() const
{
	mesh->Unload();
	material->shader.Unbind();
	material->mainTexture.Unbind();
}