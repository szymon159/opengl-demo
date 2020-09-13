#pragma once

#include "includes.hpp"

#include "model.hpp"
#include "camera.hpp"
#include "lightModel.hpp"

class Shader;

class Scene
{
public:
	Scene(glm::mat4 projectionMatrix, float ambientLightStrength = 0.0f, glm::vec3 ambientLightColor = glm::vec3(1.0f));

	void AddModel(Model* model);
	void AddCamera(Camera* camera);
	void AddLight(LightModel* light);
	void ToggleActiveCamera(int newActiveCameraId);
	void SetAmbient(float ambientStrength, glm::vec3 ambientColor);
	void Update();
	bool Draw();

private:
	glm::mat4 projectionMatrix;
	std::vector<Model*> models;
	std::vector<Camera*> cameras;
	std::vector<LightModel*> lights;
	int modelsCount;
	int camerasCount;
	int lightsCount;
	int activeCameraId;
	glm::vec3 ambient;
};