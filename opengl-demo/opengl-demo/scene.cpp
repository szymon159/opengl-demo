#include "scene.hpp"

#include "shader.hpp"

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
	shader->SetVec3("spotLight.ambient", ambient);
	shader->SetVec3("pointLight.ambient", ambient);
	shader->SetVec3("dirLight.ambient", ambient);

	models.push_back(model);
	modelsCount++;
}

void Scene::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
	camerasCount++;
}

void Scene::AddLight(LightModel* light)
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
	}
}

void Scene::Update()
{
	for (int i = 0; i < modelsCount; i++)
	{
		models[i]->Update();
	}

	for (int i = 0; i < camerasCount; i++)
		cameras[i]->Update();

	for (int i = 0; i < lightsCount; i++)
		lights[i]->Update();
}

bool Scene::Draw()
{
	glm::mat4 viewMatrix = camerasCount == 0 ? glm::mat4() : cameras[activeCameraId]->GetViewMatrix();

	for (int i = 0; i < modelsCount; i++)
	{
		auto shader = models[i]->GetShader();
		shader->Use();

		for (const auto& light : lights)
		{
			if (!light->LightSource->SetUniforms(shader))
				return FAILURE;
		}

		if (!models[i]->Draw(viewMatrix, projectionMatrix, cameras[activeCameraId]->Position))
			return FAILURE;
	}

	//for (int i = 0; i < lightsCount; i++)
	//{
	//	if (!lights[i]->Draw(viewMatrix, projectionMatrix, cameras[activeCameraId]->Position))
	//		return FAILURE;
	//}

	return SUCCESS;
}

glm::vec3 Scene::GetAmbient()
{
	return ambient;
}
