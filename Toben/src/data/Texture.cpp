#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#include "../tobcore.h"

Texture::Texture(const std::string& path)
{
	data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data == NULL)
		Logger::Log(std::string("Failed to load texture ").append(path));
}

Texture::~Texture()
{
	if (data != NULL)
		stbi_image_free(data);
}
