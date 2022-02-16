#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image/stb_image.h"
#include "../core.h"

Texture::Texture(const std::string& path, bool freeData)
{
	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(path.c_str(), &width, &height, &channels, 4);
	if (data == NULL)
		Logger::Log(std::string("Failed to load texture ").append(path));

	std::cout << stbi_failure_reason << std::endl;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//unsigned char test[16] = {0, 0, 0, 255, 0, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255};
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, test);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (freeData && data != NULL)
		stbi_image_free(data);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texID);

	//if (data != NULL)
	//	stbi_image_free(data);
}
