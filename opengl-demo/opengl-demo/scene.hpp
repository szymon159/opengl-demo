#pragma once

#include "includes.hpp"

#include "model.hpp"
#include "camera.hpp"
#include "lightModel.hpp"

class Shader;

class Scene
{
public:
	Scene(glm::mat4 projectionMatrix, Shader *gouraudShader, Shader *phongShader, float ambientLightStrength = 0.0f, glm::vec3 ambientLightColor = glm::vec3(1.0f));

	void AddModel(Model* model);
	void AddCamera(Camera* camera);
	void AddLight(LightModel* light);
	void ToggleActiveCamera(int newActiveCameraId);
	void ToggleGouraudShading();
	void ToggleBlinnLighting();
	void SetAmbient(float ambientStrength, glm::vec3 ambientColor);
	void Update();
	bool Draw();
	Shader* GetActiveShader();

	glm::vec3 GetAmbient();

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
	bool useBlinn;
	Shader* gouraudShader;
	Shader* phongShader;
	bool useGouraud;
};