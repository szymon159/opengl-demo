#pragma once

#include "includes.hpp"

#include "vertex.hpp"
#include "texture.hpp"

class Shader;

struct Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures);
	void Draw(Shader*& shader) const;

private:
	uint vaoId;

	void setupMesh();
	void setVAO();
};