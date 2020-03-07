#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

uniform float intensityFactor;
uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragmentColor;

void main()
{
	fragmentColor = mix(texture(texture1, texCoord), intensityFactor * texture(texture2, texCoord), 0.3);

	fragmentColor *= vertexColor;
}
