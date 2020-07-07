#include "Entity.h"

using namespace Engine;



Entity::Entity()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);
	scale = vec3(1, 1, 1);
}

Entity::Entity(Renderer renderer)
{
	currentRenderer = renderer;
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);
	scale = vec3(1, 1, 1);
}

Entity::Entity(int newx, int newy, int newz)
{
	moveTo(static_cast<float>(newx), static_cast<float>(newy), static_cast<float>(newz));
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);

	scale = vec3(1, 1, 1);
}

Entity::Entity(float newx, float newy, float newz)
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	posAttrib = 0;
	colAttrib = 0;
	texAttrib = 0;
	model = glm::mat4(1.0f);
	modelOriginal = glm::mat4(1.0f);
	moveTo(newx, newy, newz);
	scale = vec3(1, 1, 1);
}

Entity::Entity(vec3 v)
{
	position.x = v.x;
	position.y = v.y;
	position.z = v.z;
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

float Entity::getX()
{
	return position.x;
}
float Entity::getY()
{
	return position.y;
}
float Entity::getZ()
{
	return position.z;
}
void Entity::setX(float newx)
{
	position.x = newx;
}
void Entity::setY(float newy)
{
	position.y = newy;
}
void Entity::setZ(float newz)
{
	position.z = newz;
}

void Entity::moveTo(float newx, float newy,float newz)
{
	setX(newx);
	setY(newy);
	setZ(newz);
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

void Entity::Rotate(vec3 newRotation)
{
	model = glm::rotate(model, glm::radians(newRotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(newRotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(newRotation.z), vec3(0.0f, 0.0f, 1.0f));

	rotation += newRotation;
}

void Entity::setPosition(vec3 newTranslation)
{
	//model = glm::scale(modelOriginal, newScale);
	if (is3D)
	{
		mat4 oldModel = modelOriginal;
		/*oldModel = glm::rotate(model, glm::radians(0.f), vec3(1.0f, 0.0f, 0.0f));
		oldModel = glm::rotate(model, glm::radians(90.f), vec3(0.0f, 1.0f, 0.0f));
		oldModel = glm::rotate(model, glm::radians(0.f), vec3(0.0f, 0.0f, 1.0f));*/
		oldModel = glm::scale(modelOriginal, scale);
		
		//oldModel = glm::rotate(modelOriginal, scale);
		//oldModel = glm::rotate(modelOriginal, )
		/*oldModel = glm::rotate(model, glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
		oldModel = glm::rotate(model, glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
		oldModel = glm::rotate(model, glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));*/

		cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << endl;
		model = glm::translate(oldModel, newTranslation);
		model = glm::rotate(model, glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
		/*model = glm::rotate(modelOriginal, glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(modelOriginal, glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(modelOriginal, glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));*/
	}
	else
	{
		model = glm::translate(modelOriginal, newTranslation);
	}
	

	position = newTranslation;
}

vec3 Entity::getPosition()
{
	//cout << "Position: " << position.x << " " << position.y << " " << position.z << endl;
	return position;
}

void Entity::Scale(vec3 newScale)
{
	model = glm::scale(modelOriginal, newScale);
	scale *= newScale;
}

vec3 Engine::Entity::GetScale()
{
	//std::cout << scale.x << " , " << scale.y << std::endl;
	return scale;
}
