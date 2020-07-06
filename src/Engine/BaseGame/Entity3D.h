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

namespace Engine3D
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
		ModelsConfig config;
		int layer;
		vector<Entity3D> parent;
		list<Entity3D> children;
	public:
		Shader shader;
		Model model3D;
		Entity3D();
		~Entity3D();
		GLuint GetShader();
		vec3 GetFront();
		vec3 GetUp();
		vec3 GetRight();
		vec3 GetRotation();
		void MoveForward2Axis(float speed);
		void set(string modelPath , Color color, ModelsConfig config, bool flipUVs, Light light);
		void draw();
		void SetTexture(int meshIndex, string type, string path);
		void SetMaterial2(const char* path, GLuint type, bool flip, GLint FilteringOption);
		void SetParent(Entity3D newParent);

	};
}

#endif //ENTITY3D_H
