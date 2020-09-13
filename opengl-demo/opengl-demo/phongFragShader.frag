#version 330 core

struct  Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
//	sampler2D texture_diffuse1;
//	sampler2D texture_diffuse1;
//	float shininess;
};

in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform Material material;
uniform vec3 ambient;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 modelColor;

out vec4 fragmentColor;

void main()
{
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

	fragmentColor = vec4(finalColor, 1.0); //* texture(material.texture_diffuse1, texCoord) * texture(material.texture_diffuse2, texCoord);
}
