#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.


#ifndef ANIMATION_H
#define ANIMATION_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Material.h"

namespace Graficos1
{
	class DLLEXPORT Animation
	{
	private:
		vec2 imageCount;
		vec2 currentImage;
		vec2 finalSize;
		float totalTime;
		float switchTime;
	public:
		vec2 newTexCoords[4];
	public:
		Animation();
		Animation(vec2 imageCount, float switchTime);
		~Animation();
		void Update(int row,float& deltaTime);
		void UpdateReverse(int row, float& deltaTime);
		void SetSingleFrame(vec2 framePos);
	};
}



#endif // ANIMATION_H

#pragma warning(pop)