#include "Renderer.h"
#include "BaseGame.h"
#include <fstream>
#include <sstream>
using namespace Engine;

Renderer::Renderer() 
	:
	_red(0),
	_green(0),
	_blue(0),
	_alpha(0),
	view(glm::mat4(1.0f)),
	proj(glm::mat4(1.0f)),
	uniView(0),
	uniProj(0)
{
	SetProjection();
	mat4 initialView = glm::lookAt(glm::vec3(0.0f, 0.0f, 600.0f), VECTOR_ZERO, VECTOR_UP);
	SetView(initialView);
}


void Renderer::SetBackgroundColors(Color backgroundColor)
{
	float red = backgroundColor.GetRed() * RGBTODECIMAL;
	float green = backgroundColor.GetGreen() * RGBTODECIMAL;
	float blue = backgroundColor.GetBlue() * RGBTODECIMAL;
	float alpha = backgroundColor.GetAlpha() * RGBTODECIMAL;

	color.SetColor(red, green, blue, alpha);
}

void Renderer::ChangeBackgroundColor()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}


void Renderer::SetProjection()
{
	GLint m_viewport[4]; // esquina 0,0 y esquina resolucion (ej: 1280,720)

	glGetIntegerv(GL_VIEWPORT, m_viewport); // Getter del viewport.

	proj = glm::perspective(45.0f, static_cast<float>(m_viewport[2]) / static_cast<float>(m_viewport[3]), 1.0f, 3000.0f);
}


void Renderer::SetPosition(vec3 _position)
{
	view = glm::lookAt(_position, VECTOR_ZERO, VECTOR_UP);
}

void Renderer::Draw(unsigned int _shader, unsigned int _texture1, unsigned int _texture2, unsigned int _VertexArrayID, mat4 _model, GLuint _uniModel)
{
	glUseProgram(_shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _texture2);

	mat4 proj = GetProjection();
	mat4 view = GetView();

	glUniformMatrix4fv(_uniModel, 1, GL_FALSE, glm::value_ptr(_model));

	SetUniView(glGetUniformLocation(_shader, "view"));
	glUniformMatrix4fv(GetUniView(), 1, GL_FALSE, glm::value_ptr(view));

	SetUniProj(glGetUniformLocation(_shader, "proj"));
	glUniformMatrix4fv(GetUniProj(), 1, GL_FALSE, glm::value_ptr(proj));

	glBindVertexArray(_VertexArrayID);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
}
