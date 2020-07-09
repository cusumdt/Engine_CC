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
	skybox.Set("res/model/skybox/Skybox.fbx", Colors.White, false);
	skybox.Scale(vec3(3, 3, 3));
	skybox.SetPosition(vec3(180, -0.3f, 0));
	skybox.SetTexture(0, "texture_diffuse", "res/textures/models/skybox/Sky.jpg");

	// Configuracion de Personaje
	character.Set("res/model/character/robosurfer2.obj", Colors.White, false);
	character.Scale(vec3(1, 1, 1));
	character.SetPosition(vec3(10,0,0));
	character.Rotate(vec3(0, 0, 0));

	// Configuracion de BoundingBox Visual Temporal
	box.Set("res/model/box.fbx", Colors.White, false);
	box.SetTexture(0, "texture_diffuse", "res/model/color.jpg");
	box.Scale(vec3(character.boundingBoxMax.x + (character.boundingBoxMin.x * -1) , character.boundingBoxMax.y + (character.boundingBoxMin.y * -1), character.boundingBoxMax.z + (character.boundingBoxMin.z * -1)));
	box.SetPosition(vec3(character.GetPosition().x/ (character.boundingBoxMax.x + (character.boundingBoxMin.x * -1)), character.GetPosition().y / (character.boundingBoxMax.y + (character.boundingBoxMin.y * -1)), character.GetPosition().z / (character.boundingBoxMax.z + (character.boundingBoxMin.z * -1))));
	box.Rotate(vec3(character.GetRotation().x, character.GetRotation().y, character.GetRotation().z));

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
		box.Rotate(vec3(0, 270 * deltaTime, 0));
	}
	if (input.GetKey(GLFW_KEY_RIGHT))
	{
		character.Rotate(vec3(0, -270 * deltaTime, 0));
		box.Rotate(vec3(0, -270 * deltaTime,0));
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

	box.SetPosition(vec3(character.GetPosition().x / (character.boundingBoxMax.x + (character.boundingBoxMin.x * -1)), character.GetPosition().y / (character.boundingBoxMax.y + (character.boundingBoxMin.y * -1)), character.GetPosition().z / (character.boundingBoxMax.z + (character.boundingBoxMin.z * -1))));
	

	camera.SetFront(input.GetDirection());
	camera.SetPosition(camera.GetPosition());
	
	skybox.Draw(false);
	character.Draw(false);
	if (input.GetKey(GLFW_KEY_SPACE))
	{
		box.Draw(true);
	}
	
}

void Game::DeInitGame()
{

}
