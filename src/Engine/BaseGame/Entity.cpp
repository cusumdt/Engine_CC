#include "Entity.h"

using namespace Engine;

Entity::Entity()
	:
	VertexArrayID(0),
	VertexBuffer(0),
	position(VECTOR_ZERO),
	rotation(VECTOR_ZERO),
	scale(VECTOR_ONE),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal(glm::mat4(1.0f))
{
}

Entity::Entity(Renderer renderer)
	:
	currentRenderer(renderer),
	VertexArrayID(0),
	VertexBuffer(0),
	position(VECTOR_ZERO),
	rotation(VECTOR_ZERO),
	scale(VECTOR_ONE),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal(glm::mat4(1.0f))
{
}

Entity::Entity(int _x, int _y, int _z)
	:
	VertexArrayID(0),
	VertexBuffer(0),
	position(vec3(static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_z))),
	rotation(VECTOR_ZERO),
	scale(VECTOR_ONE),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal(glm::mat4(1.0f))
{
}

Entity::Entity(float _x, float _y, float _z)
	:
	VertexArrayID(0),
	VertexBuffer(0),
	position(vec3(_x, _y, _z)),
	rotation(VECTOR_ZERO),
	scale(VECTOR_ONE),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal(glm::mat4(1.0f))
{
}

Entity::Entity(vec3 _pos)
	:
	VertexArrayID(0),
	VertexBuffer(0),
	position(_pos),
	rotation(VECTOR_ZERO),
	scale(VECTOR_ONE),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal(glm::mat4(1.0f))
{
}


void Entity::MoveTo(float _x, float _y, float _z)
{
	SetX(_x);
	SetY(_y);
	SetZ(_z);
}

void Entity::EndDraw()
{
	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(colAttrib);
	glDisableVertexAttribArray(texAttrib);
}

void Entity::Rotate(vec3 _rotation)
{
	model = glm::rotate(model, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));

	rotation += _rotation;
}

void Entity::SetPosition(vec3 _pos)
{
	if (_3D)
	{
		
		mat4 model = modelOriginal;
		model = glm::scale(modelOriginal, scale);

		cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << endl;
		model = glm::translate(model, _pos);
		model = glm::rotate(model, glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	}
	else
	{
		model = glm::translate(modelOriginal, _pos);
	}
	position = _pos;
}

void Entity::Scale(vec3 _scale)
{
	model = glm::scale(modelOriginal, _scale);
	scale *= _scale;
}
