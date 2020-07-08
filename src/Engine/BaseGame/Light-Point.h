#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#define DLLEXPORT __declspec(dllexport)

#include "Shader.h"
#include "Light.h"

namespace Engine
{
	class DLLEXPORT LightPoint
	{
	private:
		glm::vec3 pos;
		glm::vec3 lightColor;
		float intensity;
	public:
		bool exists;
		int ID;
	public:
		LightPoint();
		LightPoint(int _id);
		~LightPoint();
		void SetLight(vec3 _pos, vec3 _color, float _intensity);
		void SetLightPos(vec3 _pos);
		void SetLightColor(vec3 _color);
		void SetIntensity(float _intensity);
		inline float GetIntensity() { return intensity; }
		inline vec3 GetPos() { return pos; }
		inline vec3 GetLightColor() { return lightColor; }

	};
}

#endif //LIGHTPOINT_H

#pragma warning(pop)