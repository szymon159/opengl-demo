#include "scene.hpp"

Scene::Scene(glm::mat4 projectionMatrix, float ambientStrength, glm::vec3 ambientColor)
	: projectionMatrix(projectionMatrix), ambient(ambientStrength * ambientColor)
{
	models.clear();
	cameras.clear();
	lights.clear();
	modelsCount = camerasCount = lightsCount = 0;
	activeCameraId = 0;
}

void Scene::AddModel(Model* model)
{
	Shader* shader = model->GetShader();

	shader->Use();
	shader->SetVec3("ambient", ambient);

	models.push_back(model);
	modelsCount++;
}

void Scene::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
	camerasCount++;
}

void Scene::AddLight(LightCube* light)
{
	lights.push_back(light);
	lightsCount++;
}

void Scene::ToggleActiveCamera(int newActiveCameraId)
{
	if (newActiveCameraId < camerasCount)
		activeCameraId = newActiveCameraId;
}

void Scene::SetAmbient(float ambientStrength, glm::vec3 ambientColor)
{
	ambient = ambientStrength * ambientColor;

	for (int i = 0; i < modelsCount; i++)
	{
		Shader* shader = models[i]->GetShader();
		
		shader->Use();
		shader->SetVec3("ambient", ambient);
	}
}

void Scene::Update()
{
	for (int i = 0; i < modelsCount; i++)
		models[i]->Update();

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

	for (int i = 0; i < lightsCount; i++)
	{
		if (!lights[i]->Draw(viewMatrix, projectionMatrix))
			return FAILURE;
	}

	return SUCCESS;
}