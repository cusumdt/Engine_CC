#include "Renderer.h"
#include "BaseGame.h"
#include <fstream>
#include <sstream>
using namespace Graficos1;

enum ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

Renderer::Renderer() :
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
	mat4 initialView = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 600.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);
	SetView(initialView);
}

ShaderProgramSource Renderer::ShaderParser(const string& filepath)
{
	ifstream stream(filepath);

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };

}

unsigned int Renderer::CompileShader(unsigned int type,const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Renderer::CreateShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
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

void Renderer::DeleteShader(unsigned int shader)
{
	glDeleteProgram(shader);
}

void Renderer::SetShader(unsigned int shader)
{
	glUseProgram(shader);
}

void Renderer::SetProjection()
{
	GLint m_viewport[4]; // esquina 0,0 y esquina resolucion (ej: 1280,720)

	glGetIntegerv(GL_VIEWPORT, m_viewport); // Getter del viewport.

	proj = glm::perspective(45.0f, (float)m_viewport[2] / (float)m_viewport[3], 1.0f, 5000.0f);
}

void Renderer::SetView(mat4 _view)
{
	view = _view;
}




void Graficos1::Renderer::SetUniProj(GLuint _uniproj)
{
	uniProj = _uniproj;
}





void Graficos1::Renderer::SetUniView(GLuint _uniview)
{
	uniView = _uniview;
}

void Renderer::SetPosition(vec3 _position)
{
	view = glm::lookAt(
		_position, // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);

}

void Renderer::Draw(unsigned int shader, unsigned int texture1, unsigned int texture2, unsigned int VertexArrayID, mat4 model, GLuint uniModel)
{
	glUseProgram(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	mat4 proj = GetProjection();
	mat4 view = GetView();

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	SetUniView(glGetUniformLocation(shader, "view"));
	glUniformMatrix4fv(GetUniView(), 1, GL_FALSE, glm::value_ptr(view));

	SetUniProj(glGetUniformLocation(shader, "proj"));
	glUniformMatrix4fv(GetUniProj(), 1, GL_FALSE, glm::value_ptr(proj));

	glBindVertexArray(VertexArrayID);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
}
