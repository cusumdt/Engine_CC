#include "BaseGame.h"


using namespace Graficos1;
using namespace Graficos2;

Renderer BaseGame::newRenderer;
LightContainer BaseGame::lightContainer;

BaseGame::BaseGame()
{
	_windowWidth = 0;
	_windowHeight = 0;
}

void BaseGame::Init(int width, int height, string windowName)
{
	newWindow.Open(width, height, windowName.c_str());
	newWindow.setRenderer(newRenderer);
	input.setWindow(newWindow.getWindow());
	BaseGame::lightContainer.SetLightContainer();
}

void BaseGame::GameLoop()
{
	while (!WindowIsClosed())
	{
		float time = (float)glfwGetTime();
		TimeStep timeStep = time - _lastFrameTime;
		_lastFrameTime = time;

		UpdateBackgroud();

		Update(timeStep);

		SwapBuffers();
	}
	DeInitGame();
	DeInit();
}

void BaseGame::SetBackgroundColors(Color backgroundColor)
{
	newRenderer.SetBackgroundColors(backgroundColor);
}

bool BaseGame::WindowIsClosed()
{
	return glfwWindowShouldClose(newWindow.getWindow());
}

void BaseGame::DeInit()
{
	glfwTerminate();
}

void BaseGame::SwapBuffers()
{
	glfwSwapBuffers(newWindow.getWindow());
	glfwPollEvents();
}

void BaseGame::UpdateBackgroud()
{
	newRenderer.ChangeBackgroundColor();
}

Renderer BaseGame::GetRenderer()
{
	return newRenderer;
}

void BaseGame::CloseApplication()
{
	glfwSetWindowShouldClose(newWindow.getWindow(), true);
}
