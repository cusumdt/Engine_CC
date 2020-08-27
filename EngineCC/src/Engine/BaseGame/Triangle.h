#ifndef TRIANGLE_H
#define TRIANGLE_H
#define DLLEXPORT __declspec(dllexport)

#include "Shape.h"

namespace Graficos1
{
	class DLLEXPORT Triangle : public Shape
	{
	private:
	public:
		Triangle();
		Triangle(int newx, int newy);
		Triangle(float newx, float newy);
		Triangle(vec2 v);
		void set(Renderer renderer, Color triangleColor);
		void draw();
	};
}

#endif //TRIANGLE_H
