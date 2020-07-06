#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include "Renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Engine
{
	class DLLEXPORT Window
	{
		private:
			GLFWwindow* window;
			Renderer windowRenderer;
			float windowHeight;
			float windowWidth;
		public:
			Window();
			bool Open(int width,int height, const char windowName[64]);
			void setRenderer(Renderer _render);
			GLFWwindow* getWindow();
			Renderer getRenderer();
			float GetWindowHeight();
			float GetWindowWidth();
			//~Window();
	};
}

#endif // WINDOW_H
