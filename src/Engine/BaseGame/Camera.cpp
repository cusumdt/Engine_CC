#include "Camera.h"
#include "BaseGame.h"

using namespace Engine;

Camera::Camera():
	rotation(VECTOR_ZERO),
	position(VECTOR_ZERO),
	front(VECTOR_BACKWARD),
	up(VECTOR_UP)
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
