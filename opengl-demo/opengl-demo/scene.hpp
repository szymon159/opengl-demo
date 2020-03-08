#pragma once

#include "includes.hpp"

#include "model.hpp"
#include "camera.hpp"

class Scene
{
public:
	Scene(glm::mat4 projectionMatrix);

	void AddModel(Model* model);
	void AddCamera(Camera* camera);
	void ToggleActiveCamera(int newActiveCameraId);
	void Update();
	bool Draw();

private:
	glm::mat4 projectionMatrix;
	std::vector<Model*> models;
	std::vector<Camera*> cameras;
	int modelsCount;
	int camerasCount;
	int activeCameraId;
};