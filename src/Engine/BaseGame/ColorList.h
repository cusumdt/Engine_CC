#ifndef COLORLIST_H
#define COLORLIST_H
#include "Color.h"

#define DLLEXPORT __declspec(dllexport)

namespace Engine
{
	class DLLEXPORT ColorList
	{
	public:
		ColorList();
		Color Red;
		Color Green;
		Color Blue;
		Color Yellow;
		Color Orange;
		Color Purple;
		Color Lime;
		Color Pink;
		Color Brown;
		Color Cyan;
		Color Magenta;
		Color Lightblue;
		Color Silver;
		Color Gold;
		Color Black;
		Color White;
		Color Gray;
		~ColorList();
	};
}

#endif //COLORLIST_H

