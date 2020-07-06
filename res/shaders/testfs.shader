#version 330 core

in vec4 Color;
out vec4 outColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	outColor = texture(texture1, TexCoord) * Color;
};