#pragma once

#include "includes.hpp"

#include "shader.hpp"

class Light
{
public:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	glm::vec3 LightColor;

	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor)
		:Ambient(ambient), Diffuse(diffuse), Specular(specular), LightColor(lightColor)
	{

	}

	virtual bool SetUniforms(Shader*& shader, std::string lightName = "")
	{
		return
			shader->SetVec3(lightName + ".ambient", Ambient) &&
			shader->SetVec3(lightName + ".diffuse", Diffuse) &&
			shader->SetVec3(lightName + ".specular", Specular) &&
			shader->SetVec3(lightName + ".lightColor", LightColor);
	}
};

class DirectionalLight: public Light
{
public:
	glm::vec3 Direction;

	DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor, glm::vec3 direction)
		:Light(ambient, diffuse, specular, lightColor), Direction(direction)
	{

	}

	bool SetUniforms(Shader*& shader, std::string lightName = "dirLight") override
	{
		lightName = lightName == "" ? "dirLight" : lightName;

		return
			Light::SetUniforms(shader, lightName) &&
			shader->SetVec3(lightName + ".direction", Direction);
	}
};

class PointLight: public Light
{
public:
	glm::vec3 Position;
	float Constant;
	float Linear;
	float Quadratic;

	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor, glm::vec3 position, float constant, float linear, float quadratic)
		:Light(ambient, diffuse, specular, lightColor), Position(position), Constant(constant), Linear(linear), Quadratic(quadratic)
	{

	}

	bool SetUniforms(Shader*& shader, std::string lightName = "pointLight") override
	{
		lightName = lightName == "" ? "pointLight" : lightName;

		return
			Light::SetUniforms(shader, lightName) ||
			!shader->SetVec3(lightName + ".position", Position) ||
			!shader->SetFloat(lightName + ".constant", Constant) ||
			!shader->SetFloat(lightName + ".linear", Linear) ||
			!shader->SetFloat(lightName + ".quadratic", Quadratic);
	}
};

class SpotLight: public Light
{
public:
	glm::vec3 Position;
	glm::vec3 Direction;
	float CutOff;
	float OuterCutOff;
	float Constant;
	float Linear;
	float Quadratic;

	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic)
		:Light(ambient, diffuse, specular, lightColor), Position(position), Direction(direction), CutOff(cutOff), OuterCutOff(outerCutOff), Constant(constant), Linear(linear), Quadratic(quadratic)
	{

	}

	bool SetUniforms(Shader*& shader, std::string lightName = "spotLight") override
	{
		lightName = lightName == "" ? "spotLight" : lightName;

		return
			Light::SetUniforms(shader, lightName) ||
			!shader->SetVec3(lightName + ".position", Position) ||
			!shader->SetVec3(lightName + ".direction", Direction) ||
			!shader->SetFloat(lightName + ".cutOff", CutOff) ||
			!shader->SetFloat(lightName + ".outerCutOff", OuterCutOff) ||
			!shader->SetFloat(lightName + ".constant", Constant) ||
			!shader->SetFloat(lightName + ".linear", Linear) ||
			!shader->SetFloat(lightName + ".quadratic", Quadratic);
	}
};