#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target, bool isStatic)
	:position(position), targetPosition(target), targetModel(nullptr), isStatic(isStatic)
{

}

void Camera::SetTargetPosition(glm::vec3 target)
{
	targetPosition = target;
}

void Camera::SetTargetModel(Model* model)
{
	targetModel = model;
}

void Camera::Update()
{
	if (targetModel)
		targetPosition = targetModel->GetGlobalPosition();
	if (!isStatic)
		position = targetPosition - glm::vec3(1.0f, 1.0f, -0.8f);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, targetPosition, glm::vec3(0.0f, 0.0f, 1.0f));
}