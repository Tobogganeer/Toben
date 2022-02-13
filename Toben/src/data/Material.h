#pragma once

#include "../vendor/glm/vec4.hpp"
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	glm::u16vec4 albedo;
	Texture mainTexture;
	Shader shader;
	float smoothness;
	float specular;
};