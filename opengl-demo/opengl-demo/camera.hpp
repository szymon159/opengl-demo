#pragma once

#include "includes.hpp"
#include "model.hpp"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target)
		:position(position), targetPosition(target), targetModel(nullptr)
	{

	}

	void SetTargetPosition(glm::vec3 target)
	{
		targetPosition = target;
	}

	void SetTargetModel(Model* model)
	{
		targetModel = model;
	}

	void Update()
	{
		if (targetModel)
			targetPosition = targetModel->GetGlobalPosition();

		// Move the camera
		//const float radius = 10.0f;
		//position.x = sin(glfwGetTime()) * radius;
		//position.z = cos(glfwGetTime()) * radius;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position, targetPosition, glm::vec3(0.0f, 0.0f, 1.0f));
	}

private:
	glm::vec3 position;
	glm::vec3 targetPosition;
	Model* targetModel;
};
