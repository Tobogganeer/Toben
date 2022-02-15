#include "Graphics.h"

void Graphics::Draw(const MeshRenderer& meshRenderer)
{
	meshRenderer.mesh->Load();
	meshRenderer.material->LoadUniforms();
}