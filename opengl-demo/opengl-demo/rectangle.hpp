#pragma once

#include "model.hpp"

class Rectangle : public Model
{
public:
	Rectangle(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, Shader* shader, std::string texturePath = "")
		:Model(texturePath == "" ? rectangleVertices : texturedRectangleVertices, RECTANGLE_VERTICES, position, angleDegrees, rotationAxis, shader, texturePath)
	{

	}
};