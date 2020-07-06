#include "Light.h"
#include "BaseGame.h"
#include "Shader.h"
using namespace Engine3D;

Light::Light()
{
	pos = vec3(0.f, 0.f, 0.f); 
	exists = false;
	ID = 0;
}

Light::Light(int id)
{
	pos = vec3(0.f, 0.f, 0.f);
	exists = false;
	ID = id;
}

Light::~Light()
{
}

void Light::SetLight(bool isDir)
{
	exists = true;
	ShaderProgramSource source = Shader::ShaderParser("res/shaders/LightShader.shader");
	shader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);

	shader.use();

	shader.setVec3("light.position", vec3(1.0f, 1.0f, 1.0f));

	shader.setVec3("viewPos", vec3(1.0f, 1.0f, 1.0f));
	shader.setBool("isDirectional", isDir);
	// light properties
	lightColor=vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.65f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.7f); // low influence
	shader.setVec3("light.ambient", ambientColor);
	shader.setVec3("light.diffuse", diffuseColor);
	shader.setVec3("light.specular", 1.5f, 1.5f, 1.5f);


	// material properties
	/*shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	shader.setInt("material.emission", 4);*/
	//shader.setFloat("material.shininess", 1.0f);

	// view/projection transformations
	mat4 proj = BaseGame::_render.GetProjection();
	mat4 view = BaseGame::_render.GetView();

	shader.setMat4("view", view);
	shader.setMat4("projection", proj);
	
}

void Engine3D::Light::SetLightPos(vec3 pos)
{
	shader.setVec3("light.position", pos);
}

void Engine3D::Light::SetViewPos(vec3 viewPos)
{
	shader.setVec3("viewPos", viewPos);
}

void Engine3D::Light::SetLightColor(vec3 color)
{
	lightColor = color;
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.65f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.7f); // low influence
	shader.setVec3("light.ambient", ambientColor);
	shader.setVec3("light.diffuse", diffuseColor);
}

void Engine3D::Light::SetAmbient(float influence)
{
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.65f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(influence); // low influence
	shader.setVec3("light.ambient", ambientColor);
}

void Engine3D::Light::SetDiffuse(float influence)
{
	glm::vec3 diffuseColor = lightColor * glm::vec3(influence); // decrease the influence
	shader.setVec3("light.diffuse", diffuseColor);
}

void Engine3D::Light::SetSpecular(vec3 specular)
{
	shader.setVec3("light.specular", specular);
}
