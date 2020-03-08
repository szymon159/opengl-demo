#pragma once

#include "model.hpp"

class Cuboid : public Model
{
public:
    Cuboid(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, Shader* shader, std::string texturePath = "")
        :Model(texturePath == "" ? cuboidVertices : texturedCuboidVertices, CUBOID_VERTICES, position, angleDegrees, rotationAxis, shader, texturePath)
    {

    }
};