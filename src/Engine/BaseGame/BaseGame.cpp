#include "BaseGame.h"
#include "Renderer.h"

using namespace Engine;

Renderer BaseGame::_render;

BaseGame::BaseGame()
{
	_windowWidth = 0;
	_windowHeight = 0;	
}

void BaseGame::Init(int width, int height, string windowName)
{
	_window.Open(width, height, windowName.c_str());
	_window.setRenderer(_render);
	input.setWindow(_window.getWindow());
}

void BaseGame::GameLoop()
{
	while (!WindowIsClosed())
	{
		float time = static_cast<float>(glfwGetTime());
		Time deltaTime = time - _lastFrameTime;
		_lastFrameTime = time;

		UpdateBackgroud();

		Update(deltaTime);

		SwapBuffers();
	}

	DeInitGame();
	DeInit();
}

void BaseGame::SetBackgroundColors(Color backgroundColor)
{
	_render.SetBackgroundColors(backgroundColor);
}

bool BaseGame::WindowIsClosed()
{
	return glfwWindowShouldClose(_window.getWindow());
}

void BaseGame::DeInit()
{
	glfwTerminate();
}

void BaseGame::SwapBuffers()
{
	glfwSwapBuffers(_window.getWindow());
	glfwPollEvents();
}

void BaseGame::UpdateBackgroud()
{
	_render.ChangeBackgroundColor();
}

Renderer BaseGame::GetRenderer()
{
	return _render;
}

void BaseGame::CloseApplication()
{
	glfwSetWindowShouldClose(_window.getWindow(), true);
}
