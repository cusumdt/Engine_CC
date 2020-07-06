#ifndef LIGHT_H
#define LIGHT_H

#define DLLEXPORT __declspec(dllexport)

#include "Shader.h"

namespace Engine3D
{
	class DLLEXPORT Light
	{
	private:
	public:
		Shader shader;
		glm::vec3 pos;
		glm::vec3 lightColor;
		bool exists;
		int ID;
		Light();
		Light(int id);
		~Light();
		void SetLight(bool isDir);
		void SetLightPos(vec3 pos);
		void SetViewPos(vec3 viewPos);
		void SetLightColor(vec3 color);
		void SetAmbient(float influence);
		void SetDiffuse(float influence);
		void SetSpecular(vec3 specular);
	};
}

#endif //LIGHT_H
