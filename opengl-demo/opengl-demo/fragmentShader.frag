#version 330 core

in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform sampler2D texture1;
uniform vec3 ambient;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 fragmentColor;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	fragmentColor = vec4(ambient + diffuse, 1.0) * texture(texture1, texCoord);
}
