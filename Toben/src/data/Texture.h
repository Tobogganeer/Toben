#pragma once

#include <string>

class Texture
{
public:
	int width, height, channels;
	unsigned int texID;
	unsigned char* data;
	std::string texName;

	Texture(const std::string& path);
	~Texture();
};