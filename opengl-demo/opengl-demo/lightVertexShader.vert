#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;

out vec3 vertexColor;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	vertexColor = vec3(1.0, 1.0, 1.0);
}
