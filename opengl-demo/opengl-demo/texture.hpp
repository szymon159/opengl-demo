#pragma once

#include "includes.hpp"

#include "textureType.hpp"

class Texture
{
public:
	uint Id;
	TextureType Type;
	std::string Path;

	Texture();
	Texture(const std::string& name, const std::string& directory, TextureType type);
	~Texture();
	std::string GetTextureName() const;
};
