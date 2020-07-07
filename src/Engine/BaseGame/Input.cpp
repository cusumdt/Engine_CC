#include "Input.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

using namespace Engine;

bool Input::firstMouseInput = true;
float Input::pitch = 0;
float Input::yaw = 0;
vec2 Input::lastMousePos = vec2(0, 0);
vec3 Input::mouseDirection = vec3(0, 0, 0);

Input::Input()
{
	window = nullptr;
}



void Input::setWindow(GLFWwindow* _window)
{
	window = _window;
	glfwSetCursorPosCallback(window, mouse_callback);

	GLint m_viewport[4]; // esquina 0,0 y esquina resolucion (ej: 1280,720)

	glGetIntegerv(GL_VIEWPORT, m_viewport); // Getter del viewport.

	lastMousePos.x = static_cast<float>(m_viewport[2]) / 2;
	lastMousePos.y = static_cast<float>(m_viewport[3]) / 2;
}

bool Input::GetInput(int key)
{
	int state = glfwGetKey(window, key);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

bool Input::GetInputDown(int key)
{
	bool keyCurrentlyPressed = glfwGetKey(window, key) == GLFW_PRESS;
	if (!isKeyPressed[key] && keyCurrentlyPressed)
	{
		isKeyPressed[key] = true;
		return true;
	}
	isKeyPressed[key] = keyCurrentlyPressed;
	return false;
}

void Input::SetMouseCaptureMode(bool isActive)
{
	if (isActive)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (Input::firstMouseInput) // initially set to true
	{
		Input::lastMousePos.x = xpos;
		Input::lastMousePos.y = ypos;
		Input::firstMouseInput = false;
	}

	float xoffset = xpos - Input::lastMousePos.x;
	float yoffset = Input::lastMousePos.y - ypos; // reversed since y-coordinates range from bottom to top
	Input::lastMousePos.x = xpos;
	Input::lastMousePos.y = ypos;

	const float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Input::yaw += xoffset;
	Input::pitch += yoffset;

	if (Input::pitch > 89.0f)
		Input::pitch = 89.0f;
	if (Input::pitch < -89.0f)
		Input::pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(Input::yaw)) * cos(glm::radians(Input::pitch));
	direction.y = sin(glm::radians(Input::pitch));
	direction.z = sin(glm::radians(Input::yaw)) * cos(glm::radians(Input::pitch));
	Input::mouseDirection = glm::normalize(direction);
}

vec3 Input::GetDirection()
{
	return Input::mouseDirection;
}
