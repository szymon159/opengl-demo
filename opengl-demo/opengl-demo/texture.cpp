#include "texture.hpp"

Texture::Texture()
	:Id(0), Type(TextureType::Diffuse), Path("")
{
}

Texture::Texture(const std::string& name, const std::string& directory, TextureType type)
	:Id(0), Type(type), Path(name)
{
	glGenTextures(1, &Id);

	int width, height, nrChannels;
	auto path = directory + '/' + name;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data == nullptr)
	{
		printf("Failed to load %s\n", path.c_str());
		return;
	}

	GLenum format = GL_RGB;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, Id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
