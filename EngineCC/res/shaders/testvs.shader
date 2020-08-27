#version 330 core

in vec4 position;
in vec4 color;
in vec2 texturePos;

out vec4 Color;
uniform mat4 myMatrix;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	Color = color;
	TexCoord = texturePos;
	gl_Position =proj * view * model * position;
};