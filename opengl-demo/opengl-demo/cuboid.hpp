#pragma once

#include "model.hpp"

class Cuboid : public Model
{
public:
	Cuboid(glm::mat4 modelMatrix)
		:Model(cuboidVertices, 36, modelMatrix)
	{

	}

    Cuboid(std::string texturePath, glm::mat4 modelMatrix)
        :Model(texturedCuboidVertices, 36, texturePath, modelMatrix)
    {

    }
};