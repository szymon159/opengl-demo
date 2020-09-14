#include "scene.hpp"

#include "shader.hpp"

Scene::Scene(glm::mat4 projectionMatrix, Shader* gouraudShader, Shader* phongShader, float ambientLightStrength, glm::vec3 ambientLightColor)
	: projectionMatrix(projectionMatrix), ambient(ambientLightStrength* ambientLightColor), gouraudShader(gouraudShader), phongShader(phongShader)
{
	models.clear();
	cameras.clear();
	lights.clear();
	modelsCount = camerasCount = lightsCount = 0;
	activeCameraId = 0;
	useBlinn = false;
	useGouraud = false;
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

void Scene::ToggleGouraudShading()
{
	useGouraud = !useGouraud;
}

void Scene::ToggleBlinnLighting()
{
	useBlinn = !useBlinn;
}

void Scene::SetAmbient(float ambientStrength, glm::vec3 ambientColor)
{
	ambient = ambientStrength * ambientColor;

	//for (int i = 0; i < modelsCount; i++)
	//{
	//	Shader* shader = models[i]->GetShader();
	//	
	//	shader->Use();
	//}
}

void Scene::Update()
{
	auto time = sin(0.3 * glfwGetTime());
	SetAmbient(time, glm::vec3(1.f));

	for (int i = 0; i < modelsCount; i++)
		models[i]->Update();

	for (int i = 0; i < camerasCount; i++)
		cameras[i]->Update();

	for (int i = 0; i < lightsCount; i++)
	{
		lights[i]->LightSource->Ambient = ambient;
		lights[i]->Update();
	}
}

bool Scene::Draw()
{
	glm::mat4 viewMatrix = camerasCount == 0 ? glm::mat4() : cameras[activeCameraId]->GetViewMatrix();

	for (int i = 0; i < modelsCount; i++)
	{
		auto shader = GetActiveShader();
		shader->Use();

		if (!shader->SetBool("useBlinn", useBlinn))
			return FAILURE;

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

Shader* Scene::GetActiveShader()
{
	return useGouraud ? gouraudShader : phongShader;
}

glm::vec3 Scene::GetAmbient()
{
	return ambient;
}
