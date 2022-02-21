#pragma once

#include "../vendor/glm/vec3.hpp"
#include "../vendor/glm/vec4.hpp"
#include "../vendor/glm/vec2.hpp"

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::u16vec2 uv;
	glm::u8vec4 colour;

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv, glm::u8vec4 colour)
		:position(position), normal(normal), colour(colour)
	{
		const int MAX = 65535;
		this->uv.x = static_cast<unsigned short>(uv.x * MAX);
		this->uv.y = static_cast<unsigned short>(uv.y * MAX);
	}

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv)
		:position(position), normal(normal), colour(255, 255, 255, 255)
	{
		const int MAX = 65535;
		this->uv.x = static_cast<unsigned short>(uv.x * MAX);
		this->uv.y = static_cast<unsigned short>(uv.y * MAX);
	}

	bool operator==(const Vertex& other)
	{
		return position == other.position && normal == other.normal
			&& uv == other.uv && colour == other.colour;
	}

	void DEBUG_DUMP()
	{
		printf("V: p%3.2f %3.2f %3.2f  t%3.2f %3.2f  n%3.2f %3.2f %3.2f \n",
			position.x, position.y, position.z, uv.x / 65535.0f, uv.y / 65535.0f, normal.x, normal.y, normal.z);
	}

	//glm::u16vec4 colour; // hdr?

	//glm::u16vec2 uv;
	//glm::u8vec4 colour;
	//char materialIndex;
};

