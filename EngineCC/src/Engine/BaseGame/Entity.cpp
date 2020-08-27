#include "Entity.h"

using namespace Graficos1;

Graficos1::Entity::~Entity()
{
}

Entity::Entity() :
	VertexArrayID(0),
	VertexBuffer(0),
	position(vec3(0, 0, 0)),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal (glm::mat4(1.0f)),
	scale(vec3(1,1,1))
{
}

Entity::Entity(Renderer renderer) :
	currentRenderer(renderer),
	VertexArrayID(0),
	VertexBuffer(0),
	position(vec3(0, 0, 0)),
	uniModel(0),
	posAttrib(0),
	colAttrib(0),
	texAttrib(0),
	model(glm::mat4(1.0f)),
	modelOriginal(glm::mat4(1.0f)),
	scale(vec3(1, 1, 1))
{
}

Entity::Entity(int _x, int _y, int _z)
{
	moveTo((float)_x, (float)_y, (float)_z);
	VertexArrayID = 0;
	VertexBuffer = 0;
	position = vec3(_x, _y, _z);
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);

	scale = vec3(1, 1, 1);
}

Entity::Entity(float _x, float _y, float _z)
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	position = vec3(_x, _y, _z);
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);
	moveTo(_x, _y, _z);
	scale = vec3(1, 1, 1);
}

Entity::Entity(vec3 v)
{
	position = v;
	VertexArrayID = 0;
	VertexBuffer = 0;
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);
	scale = vec3(1, 1, 1);
}


void Entity::setX(float _x)
{
	position.x = _x;
}
void Entity::setY(float _y)
{
	position.y = _y;
}
void Entity::setZ(float _z)
{
	position.z = _z;
}

void Entity::moveTo(float _x, float _y,float _z)
{
	setX(_x);
	setY(_y);
	setZ(_z);
}

void Entity::set()
{

}

void Entity::draw()
{

}

void Entity::endDraw()
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

void Entity::setPosition(vec3 _translation)
{
	if (is3D)
	{
		mat4 oldModel = modelOriginal;
		oldModel = glm::scale(modelOriginal, scale);

		model = glm::translate(oldModel, _translation);
		model = glm::rotate(model, glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	}
	else
	{
		model = glm::translate(modelOriginal, _translation);
	}

	position = _translation;
}


void Entity::Scale(vec3 _scale)
{
	model = glm::scale(modelOriginal, _scale);
	scale *= _scale;
}


