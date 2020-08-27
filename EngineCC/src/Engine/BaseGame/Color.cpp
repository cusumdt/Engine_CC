#include "Color.h"

using namespace Graficos1;

Color::Color()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 0;
}

Color::Color(float red, float green, float blue, float alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

void Color::SetColor(float red, float green, float blue, float alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

float Color::GetRed()
{
	return _red;
}

float Color::GetGreen()
{
	return _green;
}

float Color::GetBlue()
{
	return _blue;
}

float Color::GetAlpha()
{
	return _alpha;
}

Color::~Color()
{
}