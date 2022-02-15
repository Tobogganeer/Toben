#pragma once

#include "../vendor/glm/vec3.hpp"
#include "../vendor/glm/vec4.hpp"
#include "../vendor/glm/vec2.hpp"
#include <iostream>
#include <string>

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

	void Print()
	{
		std::cout << "vertex: " << strFromVec3(position) << " " << strFromVec3(normal) << " " << strFromVec2(uv) << " " << strFromVec4(colour) << std::endl;
	}

	std::string strFromVec2(glm::u16vec2 vec)
	{
		return std::string("v").append(std::to_string(vec.x)) + " " + std::to_string(vec.y);
	}

	std::string strFromVec3(glm::vec3 vec)
	{
		return std::string("v").append(std::to_string(vec.x)) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
	}

	std::string strFromVec4(glm::u8vec4 vec)
	{
		return std::string("v").append(std::to_string(vec.x)) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z) + " " + std::to_string(vec.w);
	}

	//glm::u16vec4 colour; // hdr?

	//glm::u16vec2 uv;
	//glm::u8vec4 colour;
	//char materialIndex;
};

