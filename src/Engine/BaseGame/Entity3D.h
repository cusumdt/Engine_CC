#ifndef ENTITY3D_H
#define ENTITY3D_H
#define DLLEXPORT __declspec(dllexport)

#include "Entity.h"
#include "Material.h"
#include "Light.h"
#include "Model.h"
#include "Shader.h"
#include <deque>


using namespace Engine;

namespace Engine
{
	class DLLEXPORT Entity3D : public Entity
	{
	protected:
		Material texture1;
		Material texture2;
		float red;
		float green;
		float blue;
		float alpha;
		vec3 front;
		vec3 up;
		vec3 right;
		SpecularMode config;
		int layer;
		vector<Entity3D> parent;
		list<Entity3D> children;
	public:
		vec3 boundingBoxMin;
		vec3 boundingBoxMax;
		Shader shader;
		Model model3D;
	public:
		Entity3D();
		~Entity3D();

		void MoveForward2Axis(float speed);
		void Draw();

		void Set(string modelPath , Color color, SpecularMode config, bool flipUVs, Light light);
		void SetTexture(int meshIndex, string type, string path);
		void SetMaterial(const char* path, GLuint type, bool flip, GLint FilteringOption);
		void SetParent(Entity3D newParent);

		inline GLuint GetShader(){return shader.ID;}
		inline vec3 GetFront() { return front; }
		inline vec3 GetUp() { return up; }
		inline vec3 GetRight() { return right; }
		inline vec3 GetRotation() { return rotation; }
	};
}

#endif //ENTITY3D_H
