#pragma warning(push)

#pragma warning(disable:4251) 


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



namespace Engine
{

	

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

			mat4 GetView();
			GLuint GetUniView();
			void SetUniView(GLuint _uniview);
			mat4 GetProjection();
			GLuint GetUniProj();
			void SetUniProj(GLuint _uniproj);
			void SetProjection();
			void SetView(mat4 newView);
			void SetPosition(vec3 newPosition);
			void Draw(unsigned int shader, unsigned int texture1, unsigned int texture2, unsigned int VertexArrayID, mat4 model, GLuint uniModel);
	};
}

#endif // RENDERER_H

#pragma warning(pop)