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
	float smoothness;
	float specular;

	Material(Shader& shader, Texture& mainTexture, float smoothness = 0.5f, float specular = 0.3f, glm::u8vec4 albedo = { 255, 255, 255, 255 })
		:shader(shader), mainTexture(mainTexture), smoothness(smoothness), specular(specular), albedo(albedo)
	{
		shader.Bind();
		shader.SetTexture("mainTex", 0);
	}

	static HeapRef<Material> Create(Shader& shader, Texture& mainTexture, float smoothness = 0.5f, float specular = 0.3f, glm::u8vec4 albedo = { 255, 255, 255, 255 })
	{
		return HeapRef<Material>(new Material(shader, mainTexture, smoothness, specular, albedo));
	}

	void LoadUniforms()
	{
		shader.Bind();
		shader.SetColour("albedo", albedo);
		shader.SetTexture("mainTex", 0);
		shader.SetFloat("smoothness", smoothness);
		shader.SetFloat("specular", smoothness);
	}
};