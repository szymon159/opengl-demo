#pragma once

#include "model.hpp"

class Cuboid : public Model
{
public:
	Cuboid(glm::vec3 position, float angleDegrees, Shader* shader)
		:Model(cuboidVertices, 36, position, angleDegrees, shader)
	{

	}

    Cuboid(glm::vec3 position, float angleDegrees, Shader* shader, std::string texturePath)
        :Model(texturedCuboidVertices, 36, position, angleDegrees, shader, texturePath)
    {

    }
};