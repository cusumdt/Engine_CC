#include "LightContainer.h"
#include "BaseGame.h"

using namespace Graficos2;

LightContainer::LightContainer() :
	pos(vec3(0,0,0)),
	exists(false),
	ID(0)
{
	
}

LightContainer::LightContainer(int id) :
	pos(vec3(0, 0, 0)),
	exists(false),
	ID(id)
{

}

LightContainer::~LightContainer()
{
}

void LightContainer::SetLightContainer()
{
	ShaderProgramSource source = BaseGame::newRenderer.ShaderParser("res/shaders/LightShader.shader");
	shader.ID = BaseGame::newRenderer.CreateShader(source.vertexSource, source.fragmentSource);

	exists = true;
	lightsTotal = 0;
}

void LightContainer::AddPointLight(LightPoint pointLight)
{
	lightsTotal++;
	pointLights.insert(pointLights.end(), pointLight);
}

void Graficos2::LightContainer::AddAmbientLight(LightAmbient _ambLight)
{
	ambLight = _ambLight;
}

void Graficos2::LightContainer::AddDirectionalLight(LightDirectional _dirLight)
{
	dirLight = _dirLight;
}

void LightContainer::SetLights()
{
	shader.use();
	shader.setInt("cantLights", lightsTotal);
	shader.setBool("hasAmbient", ambLight.exists);
	shader.setBool("hasDirectional", dirLight.exists);

	shader.setVec3("ambLight.position", ambLight.GetPos());
	shader.setVec3("dirLight.direction", dirLight.GetDirection());

	shader.setVec3("viewPos", vec3(1.0f, 1.0f, 1.0f));


	// light properties
	glm::vec3 diffuseColor = ambLight.GetLightColor() * glm::vec3(0.65f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.7f); // low influence
	shader.setVec3("ambLight.ambient", ambientColor);
	shader.setVec3("ambLight.diffuse", diffuseColor);
	shader.setVec3("ambLight.specular", 1.5f, 1.5f, 1.5f);

	glm::vec3 diffuseColorDir = dirLight.GetLightColor() * glm::vec3(0.65f); // decrease the influence
	glm::vec3 ambientColorDir = diffuseColorDir * glm::vec3(0.7f); // low influence
	shader.setVec3("dirLight.ambient", ambientColorDir);
	shader.setVec3("dirLight.diffuse", diffuseColorDir);
	shader.setVec3("dirLight.specular", 1.5f, 1.5f, 1.5f);

	for (int i = 0; i < lightsTotal; i++)
	{
		string pointLightsIndex = "pointLights[" + std::to_string(i) + "].";

		//Position
		shader.setVec3(pointLightsIndex + "position", pointLights[i].GetPos());

		//Color
		glm::vec3 diffuseColorp = pointLights[i].GetLightColor() * glm::vec3(0.65f); // decrease the influence
		glm::vec3 ambientColorp = diffuseColorp * glm::vec3(0.7f); // low influence
		shader.setVec3(pointLightsIndex + "ambient", ambientColorp);
		shader.setVec3(pointLightsIndex + "diffuse", diffuseColorp);

		//Other Values
		shader.setVec3(pointLightsIndex + "specular", 1.5f, 1.5f, 1.5f);
		shader.setFloat(pointLightsIndex + "intensity", pointLights[i].GetIntensity());
		shader.setFloat(pointLightsIndex + "constant", 0.3f);
		shader.setFloat(pointLightsIndex + "linear", 0.0014f);
		shader.setFloat(pointLightsIndex + "quadratic", 0.000007f);
	}

	// view/projection transformations
	mat4 proj = BaseGame::newRenderer.GetProjection();
	mat4 view = BaseGame::newRenderer.GetView();

	shader.setMat4("view", view);
	shader.setMat4("projection", proj);
}



