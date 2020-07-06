#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.


#ifndef GAME_H
#define GAME_H
#include "BaseGame.h"
#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Engine
{
	class DLLEXPORT Game : public BaseGame
	{
	private:
		ColorList Colors;
		Sprite background;
		float clock;
		float movementSpeed;
		Entity3D character;
		Entity3D skybox;
		Light light;
	
	public:
		Game();
		~Game();
		void InitGame();
		void Update(TimeStep deltaTime);
		void DeInitGame();

	};
}

#endif // GAME_H

#pragma warning(pop)