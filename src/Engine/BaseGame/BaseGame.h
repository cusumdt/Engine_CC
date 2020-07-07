#ifndef BASEGAME_H
#define BASEGAME_H
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Color.h"
#include "ColorList.h"
#include "Triangle.h"
#include "Sprite.h"
#include "TimeStep.h"
#include "Camera.h"
#include "Importer.h"
#include "Model.h"
#include "Entity3D.h"
#include "Light.h"


#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Engine;

namespace Engine 
{

	class DLLEXPORT BaseGame
	{
		private:
			Window _window;
			Importer_Test _importer;
			int _windowWidth;
			int _windowHeight;
			float _lastFrameTime=0.0f;
		protected:
			Camera camera;
			Input input;
		public:
			BaseGame();
			static Renderer _render;
			void Init(int width, int height, string windowName);
			void GameLoop();
			void SetBackgroundColors(Color backgroundColor);
			bool WindowIsClosed();
			void DeInit();
			void SwapBuffers();
			void UpdateBackgroud();
			void CloseApplication();
			Renderer GetRenderer();
			virtual void Update(TimeStep deltaTime) = 0;
			virtual void DeInitGame() = 0;
			static vector<Light> lights;
	};
}

#endif // BASEGAME_H