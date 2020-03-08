#pragma once

#include "includes.hpp"

// position: glm::vec3(0.0f, 0.0f, 3.0f);
// target: glm::vec3(0.0f, 0.0f, 0.0f);  

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target)
		:position(position), target(target)
	{

	}

	void Update()
	{
		const float radius = 10.0f;
		position.x = sin(glfwGetTime()) * radius;
		position.z = cos(glfwGetTime()) * radius;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position, target, glm::vec3(0.0, 1.0, 0.0));
	}

private:
	glm::vec3 position;
	glm::vec3 target;
};
