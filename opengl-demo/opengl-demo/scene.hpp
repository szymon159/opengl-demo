#pragma once

#include "includes.hpp"

#include "model.hpp"

class Scene
{
public:
	Scene(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
		: viewMatrix(viewMatrix), projectionMatrix(projectionMatrix)
	{
		models.clear();
		modelsCount = 0;
	}

	void AddModel(Model* model)
	{
		models.push_back(model);
		modelsCount++;
	}

	bool Draw()
	{
		for (int i = 0; i < modelsCount; i++)
		{
			if (!models[i]->Draw(viewMatrix, projectionMatrix))
				return FAILURE;
		}

		return SUCCESS;
	}

private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	std::vector<Model*> models;
	int modelsCount;
};