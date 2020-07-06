#include "Camera.h"
#include "BaseGame.h"

using namespace Engine3D;

Camera::Camera()
{
	rotation = vec3(0, 0, 0);
	position = vec3(0, 0, 0);
	front = vec3(0, 0, -1);
	up = vec3(0, 1, 0);
}

vec3 Camera::GetPosition()
{
	return position;
}

void Camera::SetPosition(vec3 newPosition)
{
	position = newPosition;

	mat4 newView = glm::lookAt(
		newPosition, // position
		position + front, // look at
		up  // up
	);

	BaseGame::_render.SetView(newView);
}

void Camera::SetRotation(vec3 newRotation)
{
	mat4 newView = glm::lookAt(
		position, // position
		newRotation, // look at
		up  // up
	);

	BaseGame::_render.SetView(newView);
	rotation = newRotation;
}

vec3 Camera::GetFront()
{
	return front;
}

vec3 Camera::GetUp()
{
	return up;
}

mat4 Camera::GetProjection()
{
	return BaseGame::_render.GetProjection();
}

mat4 Camera::GetView()
{
	return BaseGame::_render.GetView();
}


void Camera::SetFront(vec3 newFront)
{
	front = newFront;
}