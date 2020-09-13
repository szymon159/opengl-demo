#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 modelMatrix;
uniform mat4 inversedModelMatrix;
uniform vec3 ambient;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 modelColor;

out vec4 fragmentColor;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	vec3 fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
	vec2 texCoord = aTexCoord;
	vec3 normal = mat3(transpose(inversedModelMatrix))* aNormal; 

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	vec3 finalColor = (ambient + diffuse + specular) * modelColor;

	fragmentColor = vec4(finalColor, 1.0);
}
