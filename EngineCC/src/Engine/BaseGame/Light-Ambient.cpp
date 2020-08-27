#include "Light-Ambient.h"
#include "BaseGame.h"

using namespace Graficos2;


LightAmbient::LightAmbient() :
	pos(vec3(0, 0, 0)),
	exists(false),
	ID(0)
{
}

LightAmbient::LightAmbient(int id) :
	pos(vec3(0, 0, 0)),
	exists(false),
	ID(id)
{
}

LightAmbient::~LightAmbient()
{
}

void LightAmbient::SetLight(vec3 _pos, vec3 color)
{
	pos = _pos;
	lightColor = color;
	exists = true;
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

