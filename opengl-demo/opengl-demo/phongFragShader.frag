#version 330 core

struct  Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
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
	// ambient
	vec3 ambientComponent = ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseComponent = lightColor * diff * material.diffuse;
	
	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * material.specular;  

	vec3 finalColor = (ambientComponent + diffuseComponent + specular);

	fragmentColor = vec4(finalColor, 1.0); //* texture(material.texture_diffuse1, texCoord) * texture(material.texture_diffuse2, texCoord);
}
