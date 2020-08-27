#include "Light-Directional.h"
#include "BaseGame.h"

using namespace Graficos2;


LightDirectional::LightDirectional() :
	direction (vec3(0,0,0)),
	exists (false),
	ID(0)
{

}

LightDirectional::LightDirectional(int id) :
	direction(vec3(0, 0, 0)),
	exists(false),
	ID(id)
{

}

LightDirectional::~LightDirectional()
{
}

void LightDirectional::SetLight(vec3 _direction, vec3 color)
{
	direction = _direction;
	lightColor = color;
	exists = true;
	//add this light to the light container...
	BaseGame::lightContainer.AddDirectionalLight(*this);

}

void LightDirectional::SetLightDirection(vec3 _direction)
{
	direction = _direction;
}

void LightDirectional::SetLightColor(vec3 color)
{
	lightColor = color;
}

