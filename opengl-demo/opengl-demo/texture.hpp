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
	Texture(const std::string& name, TextureType type);
	~Texture();
	std::string GetTextureName() const;
};
