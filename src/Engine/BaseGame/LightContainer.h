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

namespace Engine
{
	class DLLEXPORT LightContainer //Contenedor de distintos tipos de luces: solo 1 ambient y 1 directional y un maximo de 10 pointlights seteadas en el shader
	{
	private:
		vector<LightPoint> pointLights;
		LightAmbient ambLight;
		LightDirectional dirLight;
	public:
		Shader shader;
		glm::vec3 pos;
		glm::vec3 lightColor;
		int lightsTotal; //cant de pointlights totales en la escena
		bool exists; //booleano que determina si hay luces en la escena y segun su valor setea el shader correspondiente
		int ID;
	public:
		LightContainer();
		LightContainer(int _id);
		~LightContainer();
		void SetLightContainer();
		void SetLights();
		void AddAmbientLight(LightAmbient _ambLight);
		void AddDirectionalLight(LightDirectional _dirLight);
		void AddPointLight(LightPoint _pointLight);


	};
}

#endif //LIGHTCONTAINER_H

#pragma warning(pop)