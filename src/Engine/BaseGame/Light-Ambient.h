#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef LIGHTAMBIENT_H
#define LIGHTAMBIENT_H

#define DLLEXPORT __declspec(dllexport)

#include "Shader.h"
#include "Light.h"

namespace Engine
{
	class DLLEXPORT LightAmbient
	{
	private:
		glm::vec3 pos;
		glm::vec3 lightColor;
	public:
		bool exists;
		int ID;
	public:
		LightAmbient();
		LightAmbient(int _id);
		~LightAmbient();
		void SetLight(vec3 _pos, vec3 _color);
		void SetLightPos(vec3 _pos);
		void SetLightColor(vec3 _color);
		inline vec3 GetPos() { return pos; }
		inline vec3 GetLightColor() { return lightColor; }

	};
}

#endif //LIGHTAMBIENT_H

#pragma warning(pop)