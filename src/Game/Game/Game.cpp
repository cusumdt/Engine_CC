#include "Game.h"

using namespace Engine;
using namespace Engine;

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
	background.SetPosition(vec3(900, -10, 0)); // 512 360
	background.Rotate(vec3(0, 270, 0));

	//Configuracion de Luces
	ambient.SetLight(vec3(0.f, 0.f, 0.f), vec3(1.0f,1.0f,1.0f));
	directional.SetLight(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
	point1.SetLight(vec3(-200.f, 0.0f, 0.f), vec3(0.0f, 0.0f, 1.0f), 1.0f);
	point2.SetLight(vec3(200.f, 5.0f, 0.f), vec3(1.0f, 0.0f, 0.0f),1.0f);
	point3.SetLight(vec3(0.0f, -400.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 3.0f);

	// Configuracion de Skybox
	skybox.Set("res/model/skybox/Skybox.fbx", false);
	skybox.Scale(vec3(3, 3, 3));
	skybox.SetPosition(vec3(180, -0.3f, 0));
	skybox.SetTexture(1,1, "texture_diffuse", "res/textures/models/skybox/Sky.jpg");
	
	// Configuracion de Personaje
	character.Set("res/model/character/box4.fbx", false);
	character.Scale(vec3(10, 10, 10));
	character.SetPosition(vec3(10,0,0));
	character.Rotate(vec3(0, 0, 0));
	character.SetTexture(1, 1, "texture_diffuse", "res/model/lambert1_Base_Color.png");
	character.SetTexture(1, 1, "texture_specular", "res/model/lambert1_Metallic.png");
	character.SetTexture(2, 1, "texture_diffuse", "res/model/lambert1_Base_Color.png");
	character.SetTexture(2, 1, "texture_specular", "res/model/lambert1_Metallic.png");
	character.SetTexture(3, 1, "texture_diffuse", "res/model/lambert1_Base_Color.png");
	character.SetTexture(3, 1, "texture_specular", "res/model/lambert1_Metallic.png");
	character.SetTexture(4, 1, "texture_diffuse", "res/model/lambert1_Base_Color.png");

	movementSpeed = 250.0f;
	input.SetMouseCaptureMode(true);
	GameLoop();
}

void Game::Update(Time deltaTime)
{

	if (input.GetKey(GLFW_KEY_D))
	{
		camera.SetPosition(camera.GetPosition() + glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * movementSpeed * static_cast<float>(deltaTime));
	}

	if (input.GetKey(GLFW_KEY_A))
	{

		camera.SetPosition(camera.GetPosition() - glm::normalize(glm::cross(camera.GetFront(),camera.GetUp())) * movementSpeed * static_cast<float>(deltaTime));
	}

	if (input.GetKey(GLFW_KEY_W))
	{

		camera.SetPosition(camera.GetPosition() + (camera.GetFront() * movementSpeed * static_cast<float>(deltaTime)));
	}

	if (input.GetKey(GLFW_KEY_S))
	{
		camera.SetPosition(camera.GetPosition() - (camera.GetFront() * movementSpeed * static_cast<float>(deltaTime)));
	}

	if (input.GetKey(GLFW_KEY_Q))
	{
		camera.SetPosition(camera.GetPosition() - (camera.GetUp() * movementSpeed * static_cast<float>(deltaTime)));
	}

	if (input.GetKey(GLFW_KEY_E))
	{
		camera.SetPosition(camera.GetPosition() - (-camera.GetUp() * movementSpeed * static_cast<float>(deltaTime)));
	}

	if (input.GetKey(GLFW_KEY_LEFT))
	{
		character.Rotate(vec3(0, 270 * deltaTime, 0));

	}
	if (input.GetKey(GLFW_KEY_RIGHT))
	{
		character.Rotate(vec3(0, -270 * deltaTime, 0));

	}
	if (input.GetKey(GLFW_KEY_UP))
	{
		character.MoveForward2Axis(90 * deltaTime);
	}
	if (input.GetKey(GLFW_KEY_DOWN))
	{
		character.MoveForward2Axis(-90 * deltaTime);
	}

	if (input.GetKey(GLFW_KEY_ESCAPE))
	{
		CloseApplication();
	}
	
	if (input.GetKey(GLFW_KEY_Z))
	{
		character.GetChild("pCube2")->Rotate(vec3(0, 270 * deltaTime, 0), character.GetChild("pCube1")->worldModel);
	}
	if (input.GetKey(GLFW_KEY_X))
	{
		character.GetChild("pCube2")->Rotate(vec3(0, -270 * deltaTime, 0), character.GetChild("pCube1")->worldModel);
	}

	camera.SetFront(input.GetDirection());
	camera.SetPosition(camera.GetPosition());
	
	skybox.Draw();
	character.Draw();
}

void Game::DeInitGame()
{

}
