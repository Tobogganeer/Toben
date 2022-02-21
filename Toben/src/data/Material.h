#pragma once

#include "../vendor/glm/vec4.hpp"
#include "Texture.h"
#include "Shader.h"
#include "../utils/HeapData.h"

class Material
{
public:
	glm::u8vec4 albedo;
	Texture mainTexture;
	Shader shader;
	float specular;

	Material(Shader& shader, Texture& mainTexture, float specular = 0.3f, glm::u8vec4 albedo = { 255, 255, 255, 255 })
		:shader(shader), mainTexture(mainTexture), specular(specular), albedo(albedo)
	{
		shader.Bind();
		shader.SetTexture("mainTex", 0);
	}

	static HeapRef<Material> Create(Shader& shader, Texture& mainTexture, float specular = 0.3f, glm::u8vec4 albedo = { 255, 255, 255, 255 })
	{
		return HeapRef<Material>(new Material(shader, mainTexture, specular, albedo));
	}

	void LoadUniforms()
	{
		shader.Bind();
		shader.SetColour("albedo", albedo);
		shader.SetTexture("mainTex", 0);
		shader.SetFloat("specular", specular);

		//uniform vec3 lightColour;
		//uniform vec3 lightDir;
	}
};