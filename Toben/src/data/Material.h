#pragma once

#include "../vendor/glm/vec4.hpp"
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	glm::u8vec4 albedo;
	Texture mainTexture;
	Shader shader;
	float smoothness;
	float specular;

	void LoadUniforms()
	{
		shader.Bind();
		shader.SetColour("albedo", albedo);
		shader.SetTexture("mainTex", mainTexture.texID);
		shader.SetFloat("smoothness", smoothness);
		shader.SetFloat("specular", smoothness);
	}
};