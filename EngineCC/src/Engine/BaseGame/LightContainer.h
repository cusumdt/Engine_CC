#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef LIGHTCONTAINER_H
#define LIGHTCONTAINER_H

#define DLLEXPORT __declspec(dllexport)

#include "Shader.h"
#include "Light-Point.h"
#include "Light-Ambient.h"
#include "Light-Directional.h"
#include <vector>

namespace Graficos2
{
	class DLLEXPORT LightContainer
	{
	private:
		vector<LightPoint> pointLights;
		LightAmbient ambLight;
		LightDirectional dirLight;
	public:
		Shader shader;
		glm::vec3 pos;
		glm::vec3 lightColor;
		int lightsTotal;
		bool exists;
		int ID;
	public:
		LightContainer();
		LightContainer(int id);
		~LightContainer();
		void SetLightContainer();
		void SetLights();
		void AddAmbientLight(LightAmbient _ambLight);
		void AddDirectionalLight(LightDirectional _dirLight);
		void AddPointLight(LightPoint pointLight);
	};
}

#endif //LIGHTCONTAINER_H

#pragma warning(pop)