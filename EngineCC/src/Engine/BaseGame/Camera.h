#pragma warning(push)

#pragma warning(disable:4251) 

#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include "Renderer.h"
#define DLLEXPORT __declspec(dllexport)

using namespace std;
using namespace Graficos1;

namespace Graficos2
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
		inline vec3 GetPosition() { return position; }
		inline vec3 GetFront() { return front; }
		inline vec3 GetUp() { return up; }
		mat4 GetProjection();
		mat4 GetView();
		void SetPosition(vec3 _position);
		void SetRotation(vec3 _rotation);
		void SetFront(vec3 _front);
	};
}

#endif // CAMERA_H

#pragma warning(pop)