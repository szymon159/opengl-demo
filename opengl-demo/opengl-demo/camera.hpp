#pragma once

#include "includes.hpp"
#include "model.hpp"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, bool isStatic = true)
		:position(position), targetPosition(target), targetModel(nullptr), isStatic(isStatic)
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
		if (!isStatic)
			position = targetPosition - glm::vec3(1.0f);
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position, targetPosition, glm::vec3(0.0f, 0.0f, 1.0f));
	}

private:
	glm::vec3 position;
	glm::vec3 targetPosition;
	bool isStatic;
	Model* targetModel;
};
