#pragma once

#include "includes.hpp"

#include "model.hpp"
#include "camera.hpp"

class Scene
{
public:
	Scene(glm::mat4 projectionMatrix)
		: projectionMatrix(projectionMatrix)
	{
		models.clear();
		cameras.clear();
		modelsCount = camerasCount = 0;
		activeCameraId = 0;
	}

	void AddModel(Model* model)
	{
		models.push_back(model);
		modelsCount++;
	}

	void AddCamera(Camera* camera)
	{
		cameras.push_back(camera);
		camerasCount++;
	}

	void ToggleActiveCamera(int newActiveCameraId)
	{
		if (newActiveCameraId < camerasCount)
			activeCameraId = newActiveCameraId;
	}

	void Update()
	{
		// TODO: Do it in some other way
		models[1]->Update();

		for (int i = 0; i < camerasCount; i++)
			cameras[i]->Update();
	}

	bool Draw()
	{
		glm::mat4 viewMatrix = camerasCount == 0 ? glm::mat4() : cameras[activeCameraId]->GetViewMatrix();

		for (int i = 0; i < modelsCount; i++)
		{
			if (!models[i]->Draw(viewMatrix, projectionMatrix))
				return FAILURE;
		}

		return SUCCESS;
	}

private:
	glm::mat4 projectionMatrix;
	std::vector<Model*> models;
	std::vector<Camera*> cameras;
	int modelsCount;
	int camerasCount;
	int activeCameraId;
};