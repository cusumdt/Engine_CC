#include "Camera.h"
#include "BaseGame.h"

using namespace Engine;

Camera::Camera():
	rotation(vec3(0, 0, 0)),
	position(vec3(0, 0, 0)),
	front(vec3(0, 0, -1)),
	up(vec3(0, 1, 0))
	{
	}

void Camera::SetPosition(vec3 _position)
{
	position = _position;
	mat4 newView = glm::lookAt(_position,position + front,up);
	BaseGame::_render.SetView(newView);
}

void Camera::SetRotation(vec3 _rotation)
{
	mat4 newView = glm::lookAt(position, _rotation, up);
	BaseGame::_render.SetView(newView);
	rotation = _rotation;
}
