#pragma once

#include "includes.hpp"

#include "shader.hpp"
#include "material.hpp"
#include "light.hpp"

// TODO: Move to cpp file when adding more methods
class LightModel :public Model
{
public:
    Light* LightSource;

	LightModel(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Scene* scene, Light* light)
		: Model(position, angleDegrees, rotationAxis, scale, scene, "models/cube.obj", Material::LightSource(light->LightColor)), LightSource(light)
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
        

        return Model::Draw(viewMatrix, projectionMatrix, viewPos);
    }
};