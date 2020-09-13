#include "texture.hpp"

Texture::Texture()
	:Id(0), Type(TextureType::Diffuse), Path("")
{
}

Texture::Texture(const std::string& name, TextureType type)
	:Id(0), Type(type), Path(name)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);

	if (data == nullptr)
	{
		printf("Failed to load %s", name.c_str());
		return;
	}

	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &Id);
}

std::string Texture::GetTextureName() const
{
	switch (Type)
	{
	case TextureType::Diffuse:
		return "texture_diffuse";
	case TextureType::Specular:
		return "texture_specular";
	}

	return "texture_invalid";
}
