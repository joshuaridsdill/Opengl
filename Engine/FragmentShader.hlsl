#version 330 core

layout(location = 0) out vec4 color;

in vec3 outColor;

void main()
{
	color = vec4(outColor, 1.0);
};