#include "ColorList.h"

using namespace Graficos1;

ColorList::ColorList()
{
	Red.SetColor(255, 0, 0, 255);
	Blue.SetColor(0, 0, 255, 255);
	Green.SetColor(0, 128, 0, 255);
	Yellow.SetColor(255, 255, 0, 255);
	Orange.SetColor(255, 165, 0, 255);
	Lime.SetColor(0, 255, 0, 255);
	Brown.SetColor(150,65,0,255);
	Pink.SetColor(255,192,203,255);
	Purple.SetColor(128, 0, 128, 255);
	Lightblue.SetColor(173,216,230,255);
	Magenta.SetColor(255,0, 255,255);
	Cyan.SetColor(0, 255, 255, 255);
	Gold.SetColor(255, 215, 0,255);
	Silver.SetColor(192, 192, 192, 255);
	White.SetColor(255, 255, 255, 255);
	Black.SetColor(0, 0, 0, 255);
	Gray.SetColor(130, 130, 130, 255);
}

ColorList::~ColorList()
{
}