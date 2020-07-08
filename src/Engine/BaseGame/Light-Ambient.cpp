#include "Light-Ambient.h"
#include "BaseGame.h"

using namespace Engine;


LightAmbient::LightAmbient()
	:
	pos(VECTOR_ZERO),
	exists(false),
	ID(0)
{

}

LightAmbient::LightAmbient(int _id)
	:
	pos (VECTOR_ZERO),
	exists(false),
	ID(_id)
{

}

LightAmbient::~LightAmbient()
{
}

void LightAmbient::SetLight(vec3 _pos, vec3 _color) //cuando se setea la luz se agrega al container
{
	pos = _pos;
	lightColor = _color;
	exists = true;
	//add this light to the light container...
	BaseGame::lightContainer.AddAmbientLight(*this);

}

void LightAmbient::SetLightPos(vec3 _pos)
{
	pos = _pos;
}

void LightAmbient::SetLightColor(vec3 color)
{
	lightColor = color;
}
