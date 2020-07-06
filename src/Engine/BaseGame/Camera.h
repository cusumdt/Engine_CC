#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include "Renderer.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Engine;

namespace Engine3D
{
	class DLLEXPORT Camera
	{
	private:
		vec3 position;
		vec3 rotation;
		vec3 front;
		vec3 up;
	public:
		Camera();
		vec3 GetPosition();
		vec3 GetFront();
		vec3 GetUp();
		mat4 GetProjection();
		mat4 GetView();
		void SetPosition(vec3 newPosition);
		void SetRotation(vec3 newRotation);
		void SetFront(vec3 newFront);
	};
}

#endif // CAMERA_H