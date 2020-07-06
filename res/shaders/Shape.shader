#shader vertex
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

#shader fragment
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