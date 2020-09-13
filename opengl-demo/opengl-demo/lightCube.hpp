#pragma once

#include "includes.hpp"

#include "cube.hpp"

// TODO: Move to cpp file when adding more methods
class LightCube :public Cube
{
public:
	glm::vec3 Color;

	LightCube(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, glm::vec3 lightColor)
		: Cube(position, angleDegrees, rotationAxis, scale, shader), Color(lightColor)
	{

	}

    bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
    {
        //shader->Use();
        //glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * modelMatrix;

        //// Asssign uniforms for shaders
        //// TODO: Move it to separate method?
        //if (!shader->SetVec3("color", Color) ||
        //    !shader->SetMatrix4("transform", transformationMatrix))
        //{
        //    return FAILURE;
        //}

        //glBindVertexArray(vaoId);
        //glDrawArrays(GL_TRIANGLES, 0, verticesCount);
        //glUseProgram(0);

        return SUCCESS;
    }

    // Light is ignored as no other light can change color of light source
    bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) override
    {
        return Draw(viewMatrix, projectionMatrix);
    }

};