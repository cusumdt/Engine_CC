#ifndef BASEGAME_H
#define BASEGAME_H
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Color.h"
#include "ColorList.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sprite.h"
#include "TimeStep.h"
#include "Camera.h"
#include "Importer.h"
#include "Model.h"
#include "Entity3D.h"
#include "Text.h"
#include "LightContainer.h"
#include "testaabb.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Graficos2;

namespace Graficos1 
{
	class DLLEXPORT BaseGame 
	{
		private:
			Window newWindow;
			Importer_Test testImp;
			int _windowWidth;
			int _windowHeight;
			float _lastFrameTime=0.0f;
		protected:
			Camera camera;
			Input input;
		public:
			static LightContainer lightContainer;
			static Renderer newRenderer;
		public:
			BaseGame();
			void Init(int width, int height, string windowName);
			void GameLoop();
			void SetBackgroundColors(Color backgroundColor);
			bool WindowIsClosed();
			void DeInit();
			void SwapBuffers();
			void UpdateBackgroud();
			void CloseApplication();
			Renderer GetRenderer();
			virtual void Update(TimeStep dt) = 0;
			virtual void DeInitGame() = 0;
	};
}

#endif // BASEGAME_H