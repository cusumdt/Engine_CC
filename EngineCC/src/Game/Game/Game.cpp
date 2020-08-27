#include "Game.h"

using namespace Graficos1;
using namespace Graficos2;

Game::Game()
{
	colliding = false;
	lastPos = vec3(0, 0, 0);
	timer = 0;
	isSprite2 = false;
	lastPos2 = vec3(0, 0, 0);
	movementSpeed = 0;
}

Game::~Game()
{

}

void Game::InitGame()
{
	Color red;
	red.SetColor(255, 0, 0, 255);
	SetBackgroundColors(Colors.Black);
	Init(1024,720, "EngineCC");

	testAmbLight.SetLight(vec3(100.f, 100.0f, 100.f), vec3(.0f, .0f, .0f));
	testDirLight.SetLight(vec3(-140.f, 5.0f, 0.f), vec3(1.0f, 1.0f, 1.0f));
	testLight.SetLight(vec3(10.f, -5.0f, 0.f), vec3(0.0f, 0.0f, 1.0f), 1.0f);
	testLight2.SetLight(vec3(-1000.f, 5.0f, 0.f), vec3(0.0f, 1.0f, 0.0f), 3.0f);

	//// FBX TANK (With child nodes)
	tank.set("res/model/tankv5.fbx", false);
	tank.Scale(vec3(20, 20, 20));
	tank.setPosition(vec3(0, 0, 0));
	tank.Rotate(vec3(0, 29, 0));
	tank.SetTexture(1, 1, "texture_diffuse", "res/textures/models/tank/lambert1_Base_Color.png");
	tank.SetTexture(1, 1, "texture_specular", "res/textures/models/tank/lambert1_Metallic.png");
	tank.SetTexture(2, 1, "texture_diffuse", "res/textures/models/tank/lambert1_Base_Color.png");
	tank.SetTexture(2, 1, "texture_specular", "res/textures/models/tank/lambert1_Metallic.png");
	tank.SetTexture(3, 1, "texture_diffuse", "res/textures/models/tank/lambert1_Base_Color.png");
	tank.SetTexture(3, 1, "texture_specular", "res/textures/models/tank/lambert1_Metallic.png");
	tank.SetTexture(4, 1, "texture_diffuse", "res/textures/models/tank/lambert1_Base_Color.png");

	//// FBX TEXTURE CONFIG MANUAL
	skybox.set("res/model/skybox/SkyPano_SerpentineValley.fbx", true);
	skybox.Scale(vec3(6, 6, 6));
	skybox.setPosition(vec3(0, 0.f, 0));
	skybox.SetTexture(1, 1, "texture_diffuse", "res/textures/models/skybox/Serpentine_Valley_8k.jpg");




	movementSpeed = 240.0f;
	camera.SetPosition(vec3(0, 0, 0));

	input.SetMouseCaptureMode(true);

	GameLoop();
}

void Game::Update(TimeStep dt)
{
	timer += dt;
	if (input.GetInput(GLFW_KEY_D))
	{
		camera.SetPosition(camera.GetPosition() + glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * movementSpeed * (float)dt);
	}

	if (input.GetInput(GLFW_KEY_A))
	{
		camera.SetPosition(camera.GetPosition() - glm::normalize(glm::cross(camera.GetFront(),camera.GetUp())) * movementSpeed * (float)dt);
	}

	if (input.GetInput(GLFW_KEY_W))
	{

		camera.SetPosition(camera.GetPosition() + (camera.GetFront() * movementSpeed * (float)dt));
	}

	if (input.GetInput(GLFW_KEY_S))
	{
		camera.SetPosition(camera.GetPosition() - (camera.GetFront() * movementSpeed * (float)dt));
	}

	if (input.GetInput(GLFW_KEY_LEFT))
	{
		tank.Rotate(vec3(0, 270 * dt, 0));
	}
	if (input.GetInput(GLFW_KEY_RIGHT))
	{
		tank.Rotate(vec3(0, -270 * dt, 0));
	}
	if (input.GetInput(GLFW_KEY_UP))
	{
		tank.setPosition(vec3(3.f * dt , 0, 0));		
	}
	if (input.GetInput(GLFW_KEY_DOWN))
	{
		tank.setPosition(vec3(-3.f * dt, 0, 0));
	}

	if (input.GetInput(GLFW_KEY_Q))
	{
		tank.GetChild("turret_cannon")->Rotate(vec3(0, 270 * dt, 0), tank.GetChild("turret_base")->worldModel);
	}
	if (input.GetInput(GLFW_KEY_E))
	{
		tank.GetChild("turret_cannon")->Rotate(vec3(0, -270 * dt, 0), tank.GetChild("turret_base")->worldModel);
	}



	if (input.GetInput(GLFW_KEY_Z))
	{
		tank.GetChild("groupwheel01")->Rotate(vec3(0, 270 * dt, 0), tank.GetChild("body")->worldModel);
	}
	if (input.GetInput(GLFW_KEY_X))
	{
		tank.GetChild("groupwheel01")->Rotate(vec3(0, -270 * dt, 0), tank.GetChild("body")->worldModel);
	}
	
	tank.setPosition(vec3(0, 0, 0));

	if (input.GetInput(GLFW_KEY_ESCAPE))
	{
		CloseApplication();
	}

	camera.SetFront(input.GetDirection());
	camera.SetPosition(camera.GetPosition());
	
	skybox.draw();
	tank.draw();


}

void Game::DeInitGame()
{
}
