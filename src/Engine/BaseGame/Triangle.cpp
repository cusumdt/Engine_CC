#include "Triangle.h"
#include <fstream>
#include <sstream>
#include "Window.h"
#include "Shader.h"
using namespace Engine;

Triangle::Triangle()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;
}

Triangle::Triangle(int newx, int newy)
{
	moveTo(static_cast<float>(newx), static_cast<float>(newy),0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;
}

Triangle::Triangle(float newx, float newy)
{
	moveTo(newx, newy,0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;
}

Triangle::Triangle(vec2 v)
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;
}

void Triangle::set(Renderer renderer, Color triangleColor)
{
	currentRenderer = renderer;
	ShaderProgramSource source = Shader::ShaderParser("res/shaders/Shape.shader");
	shader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);
	shader.use();
	//glUseProgram(shader);

	mat4 proj = currentRenderer.GetProjection();
	mat4 view = currentRenderer.GetView();

	vec2 texCoords[] = 
	{
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.5f, 1.0f }
	};

	vec2 triangleVertexes[] =
	{
		{ -0.5f, -0.5f },
		{ 0.5f, -0.5f },
		{ 0.0f, 0.5f }
	};

	float red2 = triangleColor.GetRed() * RGBTODECIMAL;
	float green2 = triangleColor.GetGreen() * RGBTODECIMAL;
	float blue2 = triangleColor.GetBlue() * RGBTODECIMAL;
	float alpha2 = triangleColor.GetAlpha() * RGBTODECIMAL;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	const GLfloat g_vertex_buffer_data[] =
	{
		   triangleVertexes[0].x, triangleVertexes[0].y, red2, green2, blue2, alpha2, texCoords[0].x, texCoords[0].y,
		   triangleVertexes[1].x, triangleVertexes[1].y, red2, green2, blue2, alpha2, texCoords[1].x, texCoords[1].y,
		   triangleVertexes[2].x, triangleVertexes[2].y, red2, green2, blue2, alpha2, texCoords[2].x, texCoords[2].y
	};

	// Identificar el vertex buffer
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &VertexBuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] =
	{
		0, 1, 2
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	

	// Specify the layout of the vertex data
	posAttrib = glGetAttribLocation(shader.ID, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	colAttrib = glGetAttribLocation(shader.ID, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	texAttrib = glGetAttribLocation(shader.ID, "texturePos");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	

	uniModel = glGetUniformLocation(shader.ID, "model");
	model = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	currentRenderer.SetUniView(glGetUniformLocation(shader.ID, "view"));
	glUniformMatrix4fv(currentRenderer.GetUniView(), 1, GL_FALSE, glm::value_ptr(view));

	currentRenderer.SetUniProj(glGetUniformLocation(shader.ID, "proj"));
	glUniformMatrix4fv(currentRenderer.GetUniProj(), 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // set it manually
	glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1); // set it manually
}

void Triangle::draw()
{
	shader.use();
	//glUseProgram(shader);
	glBindVertexArray(VertexArrayID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1.GetTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2.GetTexture());
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
