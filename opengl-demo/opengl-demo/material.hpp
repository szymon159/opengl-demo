#pragma once

#include "includes.hpp"

class Material 
{
public:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	static Material Gold();
	static Material CyanRubber();
	static Material Pearl();
	static Material LightSource(glm::vec3 lightColor);
};


