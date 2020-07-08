#include "Light-Point.h"
#include "BaseGame.h"

using namespace Engine;


LightPoint::LightPoint()
	:
	pos(VECTOR_ZERO),
	exists(false),
	ID(0),
	intensity(0)
{

}
LightPoint::LightPoint(int _id)
	:
	pos(VECTOR_ZERO),
	exists(false),
	ID(_id),
	intensity(0)
{
	
}

LightPoint::~LightPoint()
{
}

void LightPoint::SetLight(vec3 _pos, vec3 _color, float _intensity)
{
	pos = _pos;
	lightColor = _color;
	intensity = _intensity;

	//add this light to the light container...
	ID = BaseGame::lightContainer.lightsTotal + 1;
	BaseGame::lightContainer.AddPointLight(*this);
	
}

void Engine::LightPoint::SetLightPos(vec3 _pos)
{
	pos = _pos;
}

void Engine::LightPoint::SetLightColor(vec3 _color)
{
	lightColor = _color;
}

void Engine::LightPoint::SetIntensity(float _intensity)
{
	intensity = _intensity;
}
