#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include "Renderer.h"

#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Engine;

namespace Engine
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
		void SetPosition(vec3 _position);
		void SetRotation(vec3 _rotation);
		inline void SetFront(vec3 _front) { front = _front; }
		inline vec3 GetPosition() { return position; }
		inline vec3 GetFront() { return front; }
		inline vec3 GetUp() { return up; }
	};
}

#endif // CAMERA_H