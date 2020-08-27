#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.


#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include "Color.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#define DLLEXPORT __declspec(dllexport)
typedef unsigned int GLuint;

using namespace std;
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

namespace Graficos1
{

	struct ShaderProgramSource
	{
		string vertexSource;
		string fragmentSource;
	};

	class DLLEXPORT Renderer
	{
		private:
			Color color;
			float _red;
			float _green;
			float _blue;
			float _alpha;
			mat4 view;
			mat4 proj;
			GLuint uniView;
			GLuint uniProj;
		public:
			Renderer();
			void SetBackgroundColors(Color backgroundColor);
			void ChangeBackgroundColor();
			void DeleteShader(unsigned int shader);
			void SetShader(unsigned int shader);
			ShaderProgramSource ShaderParser(const string& filepath);
			unsigned int CompileShader(unsigned int type, const string& source);
			unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
			void SetUniView(GLuint _uniview);
			void SetUniProj(GLuint _uniproj);
			void SetProjection();
			void SetView(mat4 _view);
			void SetPosition(vec3 _position);
			void Draw(unsigned int shader, unsigned int texture1, unsigned int texture2, unsigned int VertexArrayID, mat4 model, GLuint uniModel);
			inline mat4 GetProjection() { return proj; }
			inline GLuint GetUniProj() { return uniProj; }
			inline mat4 GetView() { return view; }
			inline GLuint GetUniView() { return uniView; }
	};
}

#endif // RENDERER_H

#pragma warning(pop)