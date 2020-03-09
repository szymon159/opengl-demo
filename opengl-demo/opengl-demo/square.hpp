#pragma once

#include "model.hpp"

#define SQUARE_VERTICES 6

constexpr float kSquareVertices[SQUARE_VERTICES * 6] =
{
     1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
     1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
     1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f
};

constexpr float kTexturedSquareVertices[SQUARE_VERTICES * 8] =
{
     1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f
};

class Square : public Model
{
public:
	Square(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, std::string texturePath = "")
		:Model(texturePath == "" ? kSquareVertices : kTexturedSquareVertices, SQUARE_VERTICES, position, angleDegrees, rotationAxis, scale, shader, texturePath)
	{

	}
};