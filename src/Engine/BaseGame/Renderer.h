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

			void SetProjection();
			void SetPosition(vec3 _position);
			inline void SetUniView(GLuint _uniview) {uniView = _uniview;}
			inline void SetUniProj(GLuint _uniproj) { uniProj = _uniproj;}
			inline void SetView(mat4 _view) { view = _view; }

			inline mat4 GetProjection() {return proj;}
			inline GLuint GetUniView() { return uniView; }
			inline GLuint GetUniProj() { return uniProj; }
			inline mat4 GetView() { return view; }

			void Draw(unsigned int _shader, unsigned int _texture1, unsigned int _texture2, unsigned int _VertexArrayID, mat4 _model, GLuint _uniModel);
	};
}

#endif // RENDERER_H

#pragma warning(pop)