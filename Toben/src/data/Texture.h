#pragma once

#include <string>

class Texture
{
public:
	int width, height, channels;
	unsigned int texID;
	unsigned char* data;
	std::string texName;

	Texture(const std::string& path, bool freeData = false);
	void Bind(unsigned int slot = 0);
	void Unbind();
	~Texture();
};