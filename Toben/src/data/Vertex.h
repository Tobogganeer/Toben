#pragma once

#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "../glm/vec2.hpp"

class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::u16vec4 colour; // hdr?

	//glm::u16vec2 uv;
	//glm::u8vec4 colour;
	char materialIndex;
};

