#ifndef ENTITY2D_H
#define ENTITY2D_H
#define DLLEXPORT __declspec(dllexport)

#include "Entity.h"
#include "Material.h"
#include "Shader.h"

using namespace Graficos2;

namespace Graficos1
{
	class DLLEXPORT Entity2D : public Entity // Shaders que se van a usar, destruye su shader, bindea shaders
	{
	protected:
		Shader shader;
		Material texture1;
		Material texture2;
		float red;
		float green;
		float blue;
		float alpha;

	public:
		Entity2D();
		~Entity2D();
		GLuint GetShader();
		void SetMaterial1(const char* path, GLuint type, bool flip, GLint FilteringOption);
		void SetMaterial2(const char* path, GLuint type, bool flip, GLint FilteringOption);
	};
}

#endif //ENTITY2D_H
