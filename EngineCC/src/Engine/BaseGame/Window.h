#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include "Renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Graficos1
{
	class DLLEXPORT Window
	{
		private:
			GLFWwindow* window;
			Renderer windowRenderer;
			int windowHeight;
			int windowWidth;
		public:
			Window();
			bool Open(int width,int height, const char windowName[64]);
			void setRenderer(Renderer newRenderer);
			inline GLFWwindow* getWindow(){ return window; }
			inline Renderer getRenderer(){ return windowRenderer; }
			inline int GetWindowHeight(){ return windowHeight; }
			inline int GetWindowWidth(){ return windowWidth; }
			//~Window();
	};
}

#endif // WINDOW_H
