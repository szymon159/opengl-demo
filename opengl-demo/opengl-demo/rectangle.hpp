#pragma once

#include "model.hpp"

class Rectangle : public Model
{
public:
	Rectangle(glm::vec3 position, float angleDegrees, Shader* shader)
		:Model(rectangleVertices, RECTANGLE_VERTICES, position, angleDegrees, shader)
	{

	}

	Rectangle(glm::vec3 position, float angleDegrees, Shader* shader, std::string texturePath)
		:Model(texturedRectangleVertices, RECTANGLE_VERTICES, position, angleDegrees, shader, texturePath)
	{

	}
};