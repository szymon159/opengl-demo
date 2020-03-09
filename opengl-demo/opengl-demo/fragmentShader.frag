#version 330 core

in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 ambient;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(ambient, 1.0) * texture(texture1, texCoord);
}
