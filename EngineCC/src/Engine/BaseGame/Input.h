#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef INPUT_H
#define INPUT_H
#include "Window.h"
#define DLLEXPORT __declspec(dllexport)

namespace Graficos1
{
	class DLLEXPORT Input
	{
	private:
		GLFWwindow* window;
		bool isKeyPressed[GLFW_KEY_LAST] = { false };
	public:
		static bool firstMouseInput;
		static vec2 lastMousePos;
		static float yaw;
		static float pitch;
		static vec3 mouseDirection;
	public:
		Input();
		~Input();
		void SetMouseCaptureMode(bool isActive);
		void setWindow(GLFWwindow* _window);
		bool GetInput(int key);
		bool GetInputDown(int key);
		vec3 GetDirection();
	};
}

#endif // INPUT_H

#pragma warning(pop)