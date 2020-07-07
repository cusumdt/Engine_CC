#include "Camera.h"
#include "Camera.h"
#include "BaseGame.h"

using namespace Engine;

Camera::Camera() :
	rotation(VECTOR_ZERO),
	position(VECTOR_ZERO),
	front(VECTOR_BACKWARD),
	up(VECTOR_UP)
{
}

void Camera::CameraLookAt(vec3 _position = VECTOR_ZERO, vec3 _rotation = VECTOR_ZERO, vec3 _up = VECTOR_UP)
{
	mat4 view = glm::lookAt(_position, _rotation, _up);
	BaseGame::_render.SetView(view);
}

void Camera::SetPosition(vec3 _position)
{
	CameraLookAt(_position, _position + front, up);
	position = _position;
}

//Existe para tener la posibilidad de cambiar rotaciones pero nosotros cambiamos la rotacion de la camara por medio del front.
void Camera::SetRotation(vec3 _rotation)
{
	CameraLookAt(position, _rotation, up);
	rotation = _rotation;
}
