#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.


#ifndef SPRITE_H
#define SPRITE_H
#define DLLEXPORT __declspec(dllexport)

#include "Entity2D.h"
#include "Animation.h"

namespace Engine
{
	class DLLEXPORT Sprite : public Entity2D
	{
	private:
		Animation animation;
		vec2 spriteVertexes[4] = { vec2(0,0) }; // Quad
	public:
		Sprite();
		Sprite(int _x, int _y);
		Sprite(float _x, float _y);
		Sprite(vec2 v);
		void set(Color spriteColor, vec3 _scale);
		void SetAnimation(vec2 imageCount, float switchTime, vec2 startingFrame);
		void UpdateSprite(int row,bool isReversed, float& deltaTime);
		void SetSingleFrame(vec2 framePos);
		void Scale(vec3 newScale);
		void draw();
	};
}

#endif //SPRITE_H

#pragma warning(pop)