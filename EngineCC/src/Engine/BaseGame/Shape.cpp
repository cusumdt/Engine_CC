#include "Shape.h"

using namespace Graficos1;

//COMENTADO POR LAS DUDAS SI HAY QUE CAMBIAR ALGO

//Shape::Shape()
//{
//	VertexArrayID = 0;
//	VertexBuffer = 0;
//	shader = 0;
//}
//
//Shape::Shape(Renderer renderer)
//{
//	VertexArrayID = 0;
//	VertexBuffer = 0;
//	shader = 0;
//	currentRenderer = renderer;
//}
//
//Shape::~Shape()
//{
//	currentRenderer.DeleteShader(shader);
//}
//
//Shape::Shape(int newx, int newy)
//{
//	moveTo(newx, newy);
//	VertexArrayID = 0;
//	VertexBuffer = 0;
//	shader = 0;
//}
//
//Shape::Shape(float newx, float newy)
//{
//	moveTo(newx, newy);
//	VertexArrayID = 0;
//	VertexBuffer = 0;
//	shader = 0;
//}
//
//Shape::Shape(vec2 v)
//{
//	vec.x = v.x;
//	vec.y = v.y;
//	VertexArrayID = 0;
//	VertexBuffer = 0;
//	shader = 0;
//}
//
//float Shape::getX()
//{ 
//	return vec.x;
//}
//float Shape::getY()
//{ 
//	return vec.y;
//}
//void Shape::setX(float newx)
//{ 
//	vec.x = newx;
//}
//void Shape::setY(float newy)
//{ 
//	vec.y = newy;
//}
//
//void Shape::moveTo(float newx, float newy)
//{
//	setX(newx);
//	setY(newy);
//}
//
//void Shape::set(Renderer renderer, Color triangleColor)
//{
//
//}
//
//void Shape::draw()
//{
//
//}
//
//void Shape::Rotate(vec3 newRotation)
//{
//	model = glm::rotate(model, glm::radians(newRotation.x), vec3(1.0f, 0.0f, 0.0f));
//	model = glm::rotate(model, glm::radians(newRotation.y), vec3(0.0f, 1.0f, 0.0f));
//	model = glm::rotate(model, glm::radians(newRotation.z), vec3(0.0f, 0.0f, 1.0f));
//}
//
//void Shape::Translate(vec3 newTranslation)
//{
//	model = glm::translate(model, vec3(newTranslation.x * .01f, newTranslation.y * .01f, newTranslation.z * .01f));
//}
//
//void Shape::Scale(vec3 newScale)
//{
//	model = glm::scale(model, newScale);
//}
//
//GLuint Shape::GetShader()
//{
//	return shader;
//}
//
//void Shape::SetMaterial1(const char* path, GLuint type, bool flip)
//{
//	texture1.SetTexture(path, type, flip);
//}
//
//void Shape::SetMaterial2(const char* path, GLuint type, bool flip)
//{
//	texture2.SetTexture(path, type, flip);
//}