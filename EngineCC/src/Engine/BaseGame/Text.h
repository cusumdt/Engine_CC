#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef TEXTRENDER_H
#define TEXTRENDER_H
#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Renderer.h"
#include "Window.h"
#include "Shader.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Graficos1;

namespace Graficos2
{
	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	class DLLEXPORT Text // Todos los metodos van a ser exportados en un .lib para saber su direccion de memoria.
	{
	public:
		unsigned int VAO, VBO;
		Shader shader;
		std::map<char, Character> Characters;
	public:
		Text();
		void set(const char* fontPath);
		void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

	};
}

#endif // TEXTRENDER_H

#pragma warning(pop)