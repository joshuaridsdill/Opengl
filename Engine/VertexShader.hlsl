#version 330 core

layout(location = 0) in vec4 position;
layout(location = 0) in vec3 aColor;

out vec3 outColor;

void main()
{
   gl_Position = vec4(position, 1.0);
   ourColor = aColor;
};