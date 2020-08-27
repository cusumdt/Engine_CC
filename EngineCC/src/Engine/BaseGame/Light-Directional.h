#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef LIGHTDIRECTIONAL_H
#define LIGHTDIRECTIONAL_H

#define DLLEXPORT __declspec(dllexport)

#include "Shader.h"
#include "Light.h"

namespace Graficos2
{
	class DLLEXPORT LightDirectional
	{
	private:
		glm::vec3 direction;
		glm::vec3 lightColor;
	public:
		bool exists;
		int ID;
	public:
		LightDirectional();
		LightDirectional(int id);
		~LightDirectional();
		void SetLight(vec3 _direction, vec3 color);
		void SetLightDirection(vec3 _direction);
		void SetLightColor(vec3 color);
		inline vec3 GetDirection() { return direction; }
		inline vec3 GetLightColor() { return lightColor; }

	};
}

#endif //LIGHTDIRECTIONAL_H

#pragma warning(pop)