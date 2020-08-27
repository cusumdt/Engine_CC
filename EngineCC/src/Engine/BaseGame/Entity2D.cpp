#include "Entity2D.h"

using namespace Graficos1;

Entity2D::Entity2D()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	//shader = 0;
	red = 0;
	green = 0;
	blue = 0;
	alpha = 0;
}

Entity2D::~Entity2D()
{
	currentRenderer.DeleteShader(shader.ID);
}

GLuint Graficos1::Entity2D::GetShader()
{
	return shader.ID;
}

void Graficos1::Entity2D::SetMaterial1(const char * path, GLuint type, bool flip, GLint FilteringOption)
{
	texture1.SetTexture(path, type, flip, FilteringOption);
}

void Graficos1::Entity2D::SetMaterial2(const char * path, GLuint type, bool flip, GLint FilteringOption)
{
	texture2.SetTexture(path, type, flip, FilteringOption);
}