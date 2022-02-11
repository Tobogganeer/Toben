#pragma once

#include "../glm/vec4.hpp"
#include "Texture.h"

class Material
{
public:
	glm::u16vec4 albedo;
	Texture mainTexture;
	float smoothness;
	float specular;
};