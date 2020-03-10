#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 modelMatrix;
uniform mat4 inversedModelMatrix;

out vec3 normal;
out vec2 texCoord;
out vec3 fragPos;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	texCoord = aTexCoord;
	normal = mat3(transpose(inversedModelMatrix))* aNormal; 
	fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
}
