#include "Camera.h"
#include "BaseGame.h"

using namespace Graficos2;

Camera::Camera() :
	rotation(vec3(0, 0, 0)),
	position(vec3(0, 0, 0)),
	front(vec3(0, 0, -1)),
	up(vec3(0, 1, 0))
{
}


void Camera::SetPosition(vec3 _position)
{
	position = _position;

	mat4 newView = glm::lookAt(
		_position, // position
		position + front, // look at
		up  // up
	);

	BaseGame::newRenderer.SetView(newView);
}

void Camera::SetRotation(vec3 _rotation)
{
	mat4 newView = glm::lookAt(
		position, // position
		_rotation, // look at
		up  // up
	);

	BaseGame::newRenderer.SetView(newView);
	rotation = _rotation;
}




void Camera::SetFront(vec3 _front)
{
	front = _front;
}

mat4 Camera::GetProjection() { return BaseGame::newRenderer.GetProjection(); }
mat4 Camera::GetView() { return BaseGame::newRenderer.GetView(); }