#include "CollisionManager.h"
using namespace std;
using namespace Engine;

CollisionManager::CollisionManager()
{
	_collided = false;
}

bool CollisionManager::ScreenCollision(glm::vec2 entityPos, glm::vec4 pixels)
{
	if (entityPos.x<pixels.x || entityPos.x > pixels.y || entityPos.y > pixels.z || entityPos.y < pixels.w)
	{
		_collided = true;
		//cout << "Esta colisionando pantalla" << endl;
	}
	else
	{
		_collided = false;
		//cout << "NO esta colisionando pantalla" << endl;
	}
	return _collided;
}

bool CollisionManager::CollisionDetection(glm::vec2 entityPos, glm::vec2 entityScale, glm::vec2 entityPos2, glm::vec2 entityScale2)
{
	if (entityPos.x - entityScale.x / 2 < entityPos2.x + entityScale2.x / 2 &&
		entityPos.x + entityScale.x / 2 > entityPos2.x - entityScale2.x / 2 &&
		entityPos.y - entityScale.y / 2 < entityPos2.y + entityScale2.y / 2 &&
		entityPos.y + entityScale.y / 2 > entityPos2.y - entityScale2.y / 2)
	{
		_collided = true;
		//cout << "Colisiona" <<endl;
	}
	else
	{
		_collided = false;
		//cout << "NONONO Colisiona" << endl;
	}
	return _collided;
}
