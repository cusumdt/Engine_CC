#include "Game.h"

using namespace Engine;
using namespace Engine3D;

Game::Game()
{
	clock = 0;
	
}

Game::~Game()
{

}

void Game::InitGame()
{
	Color red;
	red.SetColor(255, 0, 0, 255);
	SetBackgroundColors(Colors.Black);
	Init(1024,720, "Engine");

	background.set(Colors.White, vec3(1024.0f, 720.0f, 1.0f));
	background.setPosition(vec3(900, -10, 0)); // 512 360
	background.Rotate(vec3(0, 270, 0));

	
	
	light.SetLight(false);
	light.SetLightPos(vec3(10.f, -5.0f, 0.f));

	// Manual Texture
	skybox.set("res/model/skybox/Skybox.fbx", Colors.White, ModelsConfig::A, false, light);
	skybox.Scale(vec3(3, 3, 3));
	skybox.setPosition(vec3(180, -0.3f, 0));
	skybox.SetTexture(0, "texture_diffuse", "res/textures/models/skybox/Sky.jpg");
	// Mtl
	character.set("res/model/box2.fbx", Colors.White, ModelsConfig::A, false,light);
	character.Scale(vec3(1, 1, 1));
	character.setPosition(vec3(30,-10,0));
	character.Rotate(vec3(-90, 0, 0));


	movementSpeed = 250.0f;

	input.SetMouseCaptureMode(true);

	GameLoop();
	
}

void Game::Update(TimeStep deltaTime)
{

	if (input.GetInput(GLFW_KEY_D))
	{
		camera.SetPosition(camera.GetPosition() + glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * movementSpeed * static_cast<float>(deltaTime));
	}

	if (input.GetInput(GLFW_KEY_A))
	{

		camera.SetPosition(camera.GetPosition() - glm::normalize(glm::cross(camera.GetFront(),camera.GetUp())) * movementSpeed * static_cast<float>(deltaTime));
	}

	if (input.GetInput(GLFW_KEY_W))
	{

		camera.SetPosition(camera.GetPosition() + (camera.GetFront() * movementSpeed * static_cast<float>(deltaTime)));
	}

	if (input.GetInput(GLFW_KEY_S))
	{
		camera.SetPosition(camera.GetPosition() - (camera.GetFront() * movementSpeed * static_cast<float>(deltaTime)));
	}

	if (input.GetInput(GLFW_KEY_LEFT))
	{
		character.Rotate(vec3(0, 270 * deltaTime, 0));
	}
	if (input.GetInput(GLFW_KEY_RIGHT))
	{
		character.Rotate(vec3(0, -270 * deltaTime, 0));
	}
	if (input.GetInput(GLFW_KEY_UP))
	{
		character.MoveForward2Axis(90 * deltaTime);
	}
	if (input.GetInput(GLFW_KEY_DOWN))
	{
	}

	if (input.GetInput(GLFW_KEY_ESCAPE))
	{
		CloseApplication();
	}

	

	camera.SetFront(input.GetDirection());
	camera.SetPosition(camera.GetPosition());
	
	skybox.draw();
	character.draw();

}

void Game::DeInitGame()
{
}
