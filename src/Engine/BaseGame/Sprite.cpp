#include "Sprite.h"
#include <fstream>
#include <sstream>
#include "Window.h"
#include "BaseGame.h"
#include "Shader.h"
using namespace Engine;

Sprite::Sprite()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;

	spriteVertexes[0] = vec2(0, 0);
	spriteVertexes[1] = vec2(0, 0);
	spriteVertexes[2] = vec2(0, 0);
	spriteVertexes[3] = vec2(0, 0);
	
}

Sprite::Sprite(int newx, int newy)
{
	moveTo(static_cast<float>(newx), static_cast<float>(newy), 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;

	spriteVertexes[0] = vec2(0, 0);
	spriteVertexes[1] = vec2(0, 0);
	spriteVertexes[2] = vec2(0, 0);
	spriteVertexes[3] = vec2(0, 0);
}

Sprite::Sprite(float newx, float newy)
{
	moveTo(newx, newy, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;
	spriteVertexes[0] = vec2(0, 0);
	spriteVertexes[1] = vec2(0, 0);
	spriteVertexes[2] = vec2(0, 0);
	spriteVertexes[3] = vec2(0, 0);
}

Sprite::Sprite(vec2 v)
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	//shader = 0;
	spriteVertexes[0] = vec2(0, 0);
	spriteVertexes[1] = vec2(0, 0);
	spriteVertexes[2] = vec2(0, 0);
	spriteVertexes[3] = vec2(0, 0);
}

void Sprite::set(Color spriteColor, vec3 _scale)
{
	scale = _scale;
	currentRenderer = BaseGame::_render;
	ShaderProgramSource source = Shader::ShaderParser("res/shaders/Shape.shader");
	shader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);
	shader.use();
	//glUseProgram(shader.ID);
	

	mat4 proj = currentRenderer.GetProjection();
	mat4 view = currentRenderer.GetView();

	vec2 texCoords[] =
	{
		{ 0.0f, 0.0f }, // bottom-left
		{ 1, 0.0f }, // bottom-right
		{ 1, 1 }, // top-right
		{ 0.0f, 1 } // top-left
	};

	spriteVertexes[0] = { -1.f, -1.f };
	spriteVertexes[1] = { 1.f, -1.f };
	spriteVertexes[2] = { 1.f, 1.f };
	spriteVertexes[3] = { -1.f, 1.f };

	red = spriteColor.GetRed() * RGBTODECIMAL;
	green = spriteColor.GetGreen() * RGBTODECIMAL;
	blue = spriteColor.GetBlue() * RGBTODECIMAL;
	alpha = spriteColor.GetAlpha() * RGBTODECIMAL;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	const GLfloat g_vertex_buffer_data[] =
	{
		   spriteVertexes[0].x*_scale.x / 2, spriteVertexes[0].y*_scale.y / 2, red, green, blue, alpha, texCoords[0].x, texCoords[0].y,
		   spriteVertexes[1].x*_scale.x / 2, spriteVertexes[1].y*_scale.y / 2, red, green, blue, alpha, texCoords[1].x, texCoords[1].y,
		   spriteVertexes[2].x*_scale.x / 2, spriteVertexes[2].y*_scale.y / 2, red, green, blue, alpha, texCoords[2].x, texCoords[2].y,
		   spriteVertexes[3].x*_scale.x / 2, spriteVertexes[3].y*_scale.y / 2, red, green, blue, alpha, texCoords[3].x, texCoords[3].y
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
		0, 1, 2, 3
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

void Sprite::UpdateSprite(int row,bool isReversed,float& deltaTime)
{
	if (isReversed)
	{
		animation.UpdateReverse(row,deltaTime);
	}
	else
	{
		animation.Update(row, deltaTime);
	}

	const GLfloat g_vertex_buffer_data[] =
	{
		   spriteVertexes[0].x * scale.x / 2, spriteVertexes[0].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[0].x, animation.newTexCoords[0].y,
		   spriteVertexes[1].x * scale.x / 2, spriteVertexes[1].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[1].x, animation.newTexCoords[1].y,
		   spriteVertexes[2].x * scale.x / 2, spriteVertexes[2].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[2].x, animation.newTexCoords[2].y,
		   spriteVertexes[3].x * scale.x / 2, spriteVertexes[3].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[3].x, animation.newTexCoords[3].y
	};

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Sprite::SetSingleFrame(vec2 framePos)
{
	animation.SetSingleFrame(framePos);

	const GLfloat g_vertex_buffer_data[] =
	{
		   spriteVertexes[0].x * scale.x / 2, spriteVertexes[0].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[0].x, animation.newTexCoords[0].y,
		   spriteVertexes[1].x * scale.x / 2, spriteVertexes[1].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[1].x, animation.newTexCoords[1].y,
		   spriteVertexes[2].x * scale.x / 2, spriteVertexes[2].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[2].x, animation.newTexCoords[2].y,
		   spriteVertexes[3].x * scale.x / 2, spriteVertexes[3].y * scale.y / 2, red, green, blue, alpha, animation.newTexCoords[3].x, animation.newTexCoords[3].y
	};

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Sprite::SetAnimation(vec2 imageCount,float switchTime,vec2 startingFrame)
{
	Animation newAnimation(imageCount, switchTime);
	animation = newAnimation;
	SetSingleFrame(startingFrame);
}

void Sprite::draw()
{
	BaseGame::_render.Draw(shader.ID,texture1.GetTexture(),texture2.GetTexture(),VertexArrayID,model,uniModel);
}

void Sprite::Scale(vec3 newScale)
{
}
