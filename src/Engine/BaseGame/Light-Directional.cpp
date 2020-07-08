#include "Light-Directional.h"
#include "BaseGame.h"

using namespace Engine;


LightDirectional::LightDirectional()
	:
	direction(VECTOR_ZERO),
	exists(false),
	ID(0)
{
	
}

LightDirectional::LightDirectional(int _id)
	:
	direction(VECTOR_ZERO),
	exists(false),
	ID(_id)
{

}


LightDirectional::~LightDirectional()
{
}

void LightDirectional::SetLight(vec3 _direction, vec3 _color)
{
	direction = _direction;
	lightColor = _color;
	exists = true;
	//add this light to the light container...
	BaseGame::lightContainer.AddDirectionalLight(*this);

}

void LightDirectional::SetLightDirection(vec3 _direction)
{
	direction = _direction;
}

void LightDirectional::SetLightColor(vec3 _color)
{
	lightColor = _color;
}



