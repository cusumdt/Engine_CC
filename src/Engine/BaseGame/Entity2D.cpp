#include "Entity2D.h"
#include "Shader.h"
using namespace Engine;

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
	Shader::DeleteShader(shader.ID);
}

GLuint Engine::Entity2D::GetShader()
{
	return shader.ID;
}

void Engine::Entity2D::SetMaterial1(const char * path, GLuint type, bool flip, GLint FilteringOption)
{
	texture1.SetTexture(path, type, flip, FilteringOption);
}

void Engine::Entity2D::SetMaterial2(const char * path, GLuint type, bool flip, GLint FilteringOption)
{
	texture2.SetTexture(path, type, flip, FilteringOption);
}