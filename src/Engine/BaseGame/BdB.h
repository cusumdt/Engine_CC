#pragma once
#define DLLEXPORT __declspec(dllexport)

#define BOX_VERTEX 8
#include "Renderer.h"

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace std;
using namespace glm;

namespace Engine
{
	class DLLEXPORT BdB
	{
	private:
		vec3 boundingBox3D[BOX_VERTEX];
		Renderer* renderer;
	public:
		void SetVertex(vec3 _boundingBox3D[BOX_VERTEX]);
		vec3 GetVertex(int _index);
		BdB(Renderer* _renderer);
	};
}
