#pragma once

#include "model.hpp"

class Cuboid : public Model
{
public:
	Cuboid(glm::vec3 position, float angleDegrees, Shader* shader)
		:Model(cuboidVertices, CUBOID_VERTICES, position, angleDegrees, shader)
	{

	}

    Cuboid(glm::vec3 position, float angleDegrees, Shader* shader, std::string texturePath)
        :Model(texturedCuboidVertices, CUBOID_VERTICES, position, angleDegrees, shader, texturePath)
    {

    }
};