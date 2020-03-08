#include "scene.hpp"

Scene::Scene(glm::mat4 projectionMatrix)
	: projectionMatrix(projectionMatrix)
{
	models.clear();
	cameras.clear();
	modelsCount = camerasCount = 0;
	activeCameraId = 0;
}

void Scene::AddModel(Model* model)
{
	models.push_back(model);
	modelsCount++;
}

void Scene::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
	camerasCount++;
}

void Scene::ToggleActiveCamera(int newActiveCameraId)
{
	if (newActiveCameraId < camerasCount)
		activeCameraId = newActiveCameraId;
}

void Scene::Update()
{
	// TODO: Do it in some other way
	models[1]->Update();

	for (int i = 0; i < camerasCount; i++)
		cameras[i]->Update();
}

bool Scene::Draw()
{
	glm::mat4 viewMatrix = camerasCount == 0 ? glm::mat4() : cameras[activeCameraId]->GetViewMatrix();

	for (int i = 0; i < modelsCount; i++)
	{
		if (!models[i]->Draw(viewMatrix, projectionMatrix))
			return FAILURE;
	}

	return SUCCESS;
}