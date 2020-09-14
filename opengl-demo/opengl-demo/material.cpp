#include "material.hpp"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
	:Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
{
}

Material Material::Gold()
{
	return
	{
		{ 0.24725f, 0.1995f, 0.745f },
		{ 0.75164f, 0.60648f, 0.22648f },
		{ 0.628281f, 0.555802f, 0.366065f },
		0.4
	};
}

Material Material::CyanRubber()
{
	return
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.4f, 0.5f, 0.5f },
		{ 0.04f, 0.7f, 0.7f },
		0.078125f
	};
}

Material Material::Floor()
{
	return
	{
		{ 0.2f, 0.14725f, 0.14725f },
		{ 0.5f, 0.429f, 0.429f },
		{ 0.296648f, 0.296648f, 0.296648f },
		0.088f
	};
}

Material Material::Ruby()
{
	return
	{
		{ 0.1745f, 0.01175f, 0.01175f },
		{ 0.61424f, 0.04136f, 0.04136f },
		{ 0.727811f, 0.626959f, 0.626959f },
		0.6f
	};
}

Material Material::LightSource(glm::vec3 lightColor)
{
	return
	{
		lightColor,
		{ 1.f, 1.f, 1.f },
		{ 1.f, 1.f, 1.f },
		1.f
	};
}
