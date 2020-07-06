#ifndef TEXTRENDER_H
#define TEXTRENDER_H
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Renderer.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Graficos1;

namespace Graficos2
{
	//FT_FREETYPE_H

	class DLLEXPORT Text // Todos los metodos van a ser exportados en un .lib para saber su direccion de memoria.
	{
	private:

	public:
		Text();

	};
}

#endif // TEXTRENDER_H
