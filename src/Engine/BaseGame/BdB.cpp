#include "BdB.h"
using namespace Engine;

//Setea los vertices a gestionar por la bounding box
void BdB::SetVertex(vec3 _boundingBox3D[BOX_VERTEX])
{
	for (int i = 0; i < BOX_VERTEX; i++)
	{
		boundingBox3D[i] = _boundingBox3D[i];
	}
}

//Devuelve 1 vertice especifico buscado por index
vec3 BdB::GetVertex(int _index)
{
	vec4 globalRotatedPos(boundingBox3D[_index].x, boundingBox3D[_index].y, boundingBox3D[_index].z, 1.0f);

	globalRotatedPos = renderer->GetProjection() * globalRotatedPos;

	return static_cast<vec3>(globalRotatedPos);
}


BdB::BdB(Renderer* _renderer)
{
	renderer = _renderer;
	for (int i = 0; i < BOX_VERTEX; i++)
	{
		boundingBox3D[i] = vec3(0.0f, 0.0f, 0.0f);
	}
}
