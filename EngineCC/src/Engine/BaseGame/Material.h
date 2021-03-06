#ifndef MATERIAL_H
#define MATERIAL_H
#define DLLEXPORT __declspec(dllexport)

#include "stb_image.h"
#include "Window.h"

namespace Graficos1 
{
	class DLLEXPORT Material // Seteo de Texturas
	{
	private:
		unsigned int texture;
	public:
		Material();
		~Material();
		void SetTexture(const char* path, GLuint type, bool flip,GLint FilteringOption);
		inline unsigned int GetTexture() { return texture; }
	};
}

#endif //MATERIAL_H
