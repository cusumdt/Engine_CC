#include "BdB.h"
using namespace Engine;

vec3 BdB::GetVertex(int _index)
{
	vec4 globalRotatedPos(boundingBox3D[_index].x, boundingBox3D[_index].y, boundingBox3D[_index].z, 1.0f);

	globalRotatedPos = renderer->GetProjection() * globalRotatedPos;

	return (vec3)globalRotatedPos;
}

void BdB::SetVertex(vec3 _boundingBox3D[BOX_VERTEX])
{
	for (int i = 0; i < BOX_VERTEX; i++)
	{
		boundingBox3D[i] = _boundingBox3D[i];
	}
	loaded = true;
}

BdB::BdB(Renderer* _renderer)
{
	renderer = _renderer;
	for (int i = 0; i < BOX_VERTEX; i++)
	{
		boundingBox3D[i] = vec3(0.0f, 0.0f, 0.0f);
	}
	loaded = false;
}
