#include "Animation.h"

using namespace Engine;

Animation::Animation()
{
	imageCount = vec2(0,0);
	currentImage = vec2(0,0);
	finalSize = vec2(0,0);
	totalTime = 0;
	switchTime = 0;
	newTexCoords[0] = vec2(0, 0);
	newTexCoords[1] = vec2(0, 0);
	newTexCoords[2] = vec2(0, 0);
	newTexCoords[3] = vec2(0, 0);
}

Animation::Animation(vec2 imageCount, float switchTime)
{
	newTexCoords[0] = vec2(0, 0);
	newTexCoords[1] = vec2(0, 0);
	newTexCoords[2] = vec2(0, 0);
	newTexCoords[3] = vec2(0, 0);
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage.x = 0;
	currentImage.y = 0;

	finalSize.x = 1 / imageCount.x;
	finalSize.y = 1 / imageCount.y;
}

void Animation::Update(int row, float &deltaTime)
{
	currentImage.y = row;
	totalTime = deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime = 0;
		deltaTime = 0;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	newTexCoords[0] = { finalSize.x * currentImage.x, finalSize.y * currentImage.y }; // bottom-left
	newTexCoords[1] = { finalSize.x * (currentImage.x + 1), finalSize.y * currentImage.y }; // bottom-right
	newTexCoords[2] = { finalSize.x * (currentImage.x + 1), finalSize.y * (currentImage.y + 1) }; // top-right
	newTexCoords[3] = { finalSize.x * currentImage.x, finalSize.y * (currentImage.y + 1) }; // top-left
}

void Animation::UpdateReverse(int row, float& deltaTime)
{
	currentImage.y = row;
	totalTime = deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime = 0;
		deltaTime = 0;
		currentImage.x--;

		if (currentImage.x <= 0)
		{
			currentImage.x = imageCount.x;
		}
	}

	newTexCoords[0] = { finalSize.x * currentImage.x, finalSize.y * currentImage.y }; // bottom-left
	newTexCoords[1] = { finalSize.x * (currentImage.x + 1), finalSize.y * currentImage.y }; // bottom-right
	newTexCoords[2] = { finalSize.x * (currentImage.x + 1), finalSize.y * (currentImage.y + 1) }; // top-right
	newTexCoords[3] = { finalSize.x * currentImage.x, finalSize.y * (currentImage.y + 1) }; // top-left
}

void Animation::SetSingleFrame(vec2 framePos)
{
	currentImage = framePos;

	newTexCoords[0] = { finalSize.x * currentImage.x, finalSize.y * currentImage.y }; // bottom-left
	newTexCoords[1] = { finalSize.x * (currentImage.x + 1), finalSize.y * currentImage.y }; // bottom-right
	newTexCoords[2] = { finalSize.x * (currentImage.x + 1), finalSize.y * (currentImage.y + 1) }; // top-right
	newTexCoords[3] = { finalSize.x * currentImage.x, finalSize.y * (currentImage.y + 1) }; // top-left
}

Animation::~Animation()
{

}
