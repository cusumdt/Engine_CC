#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.


#ifndef GAME_H
#define GAME_H
#include "BaseGame.h"
#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Graficos1
{
	class DLLEXPORT Game : public BaseGame
	{
	private:
		bool colliding;
		bool isSprite2;
		vec3 lastPos;
		vec3 lastPos2;
		ColorList Colors;
		float timer;
		float movementSpeed;
		Entity3D tank;
		Entity3D skybox;
		LightPoint testLight;
		LightPoint testLight2;
		LightAmbient testAmbLight;
		LightDirectional testDirLight;
	public:
		Game();
		~Game();
		void InitGame();
		void Update(TimeStep dt);
		void DeInitGame();

	};
}

#endif // GAME_H

#pragma warning(pop)