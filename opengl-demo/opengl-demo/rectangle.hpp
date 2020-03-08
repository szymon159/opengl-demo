#pragma once

#include "model.hpp"

#define RECTANGLE_VERTICES 6

constexpr float rectangleVertices[RECTANGLE_VERTICES * 3] =
{
     1.0f,  1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
    -1.0f,  1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
    -1.0f, -1.0f,  0.0f,
    -1.0f,  1.0f,  0.0f
};

constexpr float texturedRectangleVertices[RECTANGLE_VERTICES * 5] =
{
     1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

class Rectangle : public Model
{
public:
	Rectangle(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, std::string texturePath = "")
		:Model(texturePath == "" ? rectangleVertices : texturedRectangleVertices, RECTANGLE_VERTICES, position, angleDegrees, rotationAxis, scale, shader, texturePath)
	{

	}
};