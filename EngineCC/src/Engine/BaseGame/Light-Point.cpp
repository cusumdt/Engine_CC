#include "Light-Point.h"
#include "BaseGame.h"

using namespace Graficos2;


LightPoint::LightPoint() :
	pos (vec3(0, 0, 0)),
	exists(false),
	ID(0),
	intensity(0)
{
}

LightPoint::LightPoint(int id) :
	pos(vec3(0, 0, 0)),
	exists(false),
	ID(id),
	intensity(0)
{

}

LightPoint::~LightPoint()
{
}

void LightPoint::SetLight(vec3 _pos, vec3 color, float _intensity)
{
	pos = _pos;
	lightColor = color;
	intensity = _intensity;

	//add this light to the light container...
	ID = BaseGame::lightContainer.lightsTotal + 1;
	BaseGame::lightContainer.AddPointLight(*this);
	
}

void Graficos2::LightPoint::SetLightPos(vec3 _pos)
{
	pos = _pos;
}

void Graficos2::LightPoint::SetLightColor(vec3 color)
{
	lightColor = color;
}

void Graficos2::LightPoint::SetIntensity(float _intensity)
{
	intensity = _intensity;
}

