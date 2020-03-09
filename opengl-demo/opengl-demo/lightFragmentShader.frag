#version 330 core

in vec3 vertexColor;

uniform vec3 ambient;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(ambient,1.0) * vec4(vertexColor, 1.0);
}
