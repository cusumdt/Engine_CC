#include "Window.h"
#include "BaseGame.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Input.h"

using namespace Engine;

Window::Window()
{
	window = nullptr;
	windowWidth = 0;
	windowHeight = 0;
}

bool Window::Open(int width, int height, const char windowName[64])
{
	windowHeight = height;
	windowWidth = width;

	/* Initialize the library */
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	return true;
}

void Window::setRenderer(Renderer _render)
{
	windowRenderer = BaseGame::_render;
	windowRenderer.SetProjection();

	mat4 initialView = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 600.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);

	windowRenderer.SetView(initialView);
}
