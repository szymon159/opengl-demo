#pragma once

#include "includes.hpp"

#include "model.hpp"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, bool isStatic = true);

	void SetTargetPosition(glm::vec3 target);
	void SetTargetModel(Model* model);
	void Update();
	glm::mat4 GetViewMatrix();

private:
	glm::vec3 position;
	glm::vec3 targetPosition;
	bool isStatic;
	Model* targetModel;
};
