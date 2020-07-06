#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#define DLLEXPORT __declspec(dllexport)

#include <iostream>
#include <glm/glm.hpp>

namespace Engine
{
	class DLLEXPORT CollisionManager
	{
	private:
		bool _collided;
	public:
		CollisionManager();
		bool ScreenCollision(glm::vec2 entityPos, glm::vec4 pixels);
		bool CollisionDetection(glm::vec2 entityPos, glm::vec2 entityScale, glm::vec2 entityPos2, glm::vec2 entityScale2);
	};
}

#endif // COLLISIONMANAGER_H
