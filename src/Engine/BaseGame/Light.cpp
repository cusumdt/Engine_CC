#include "Light.h"
#include "BaseGame.h"
#include "Shader.h"
using namespace Engine;

Light::Light()
	:
	pos(VECTOR_ZERO),
	exists(false),
	ID(0),
	lightColor(VECTOR_ONE),
	ambientStandard(0.8f),
	diffuseStandard(0.5f),
	specularStandard(vec3(2.0f))
{
}

Light::Light(int id)
	:
	pos(VECTOR_ZERO),
	exists(false),
	ID(id),
	lightColor(VECTOR_ONE),
	ambientStandard(0.8f),
	diffuseStandard(0.5f),
	specularStandard(vec3(2.0f))
{
}

void Light::SetLight(bool isDir)
{
	exists = true;
	ShaderProgramSource source = Shader::ShaderParser("res/shaders/LightShader.shader");
	shader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);

	shader.use();

	shader.setVec3("light.position", VECTOR_ONE);

	shader.setVec3("viewPos", VECTOR_ONE);
	shader.setBool("isDirectional", isDir);
	// light properties
	lightColor = VECTOR_ONE;
	glm::vec3 diffuseColor = lightColor * glm::vec3(diffuseStandard); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(ambientStandard); // low influence
	shader.setVec3("light.ambient", ambientColor);
	shader.setVec3("light.diffuse", diffuseColor);
	shader.setVec3("light.specular", specularStandard);

	// view/projection transformations
	mat4 proj = BaseGame::_render.GetProjection();
	mat4 view = BaseGame::_render.GetView();

	shader.setMat4("view", view);
	shader.setMat4("projection", proj);
	
}

void Light::SetLightPos(vec3 pos)
{
	shader.setVec3("light.position", pos);
}

void Light::SetViewPos(vec3 viewPos)
{
	shader.setVec3("viewPos", viewPos);
}

void Light::SetLightColor(vec3 color)
{
	lightColor = color;
	glm::vec3 diffuseColor = lightColor * glm::vec3(diffuseStandard); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(ambientStandard); // low influence
	shader.setVec3("light.ambient", ambientColor);
	shader.setVec3("light.diffuse", diffuseColor);
}

void Light::SetAmbient(float influence)
{
	glm::vec3 diffuseColor = lightColor * glm::vec3(diffuseStandard); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(influence); // low influence
	shader.setVec3("light.ambient", ambientColor);
}

void Light::SetDiffuse(float influence)
{
	glm::vec3 diffuseColor = lightColor * glm::vec3(influence); // decrease the influence
	shader.setVec3("light.diffuse", diffuseColor);
}

void Light::SetSpecular(vec3 specular)
{
	shader.setVec3("light.specular", specular);
}
