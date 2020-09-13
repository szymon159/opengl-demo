#pragma once

#include "includes.hpp"

#include "shader.hpp"

// TODO: Move to cpp file when adding more methods
class LightModel :public Model
{
public:
	LightModel(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, glm::vec3 lightColor)
		: Model(position, angleDegrees, rotationAxis, scale, shader, modelpth, lightColor)
	{

	}

    bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 viewPos)
    {
        // Asssign uniforms for shaders
        // TODO: Move it to separate method?
        //if (!shader->SetVec3("color", Color))
        //{
        //    return FAILURE;
        //}
        return Model::Draw(viewMatrix, projectionMatrix, Position, Color, viewPos);
    }

    // Light is ignored as no other light can change color of light source
    bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) override
    {
        return Draw(viewMatrix, projectionMatrix, viewPos);
    }

};