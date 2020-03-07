#version 330 core
in vec4 vertexColor;

uniform float intensityFactor;
out vec4 fragmentColor;

void main()
{
	fragmentColor = intensityFactor * vertexColor;
}
