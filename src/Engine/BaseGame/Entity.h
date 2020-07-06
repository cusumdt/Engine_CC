#pragma warning(push)

#pragma warning(disable:4251)


#ifndef ENTITY_H
#define ENTITY_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "CollisionManager.h"

namespace Engine
{
	class DLLEXPORT Entity
	{
	protected:
		vec3 position;
		vec3 scale;
		vec3 rotation;
		GLuint VertexArrayID;
		GLuint VertexBuffer;
		GLuint uniModel;
		GLint posAttrib;
		GLint colAttrib;
		GLint texAttrib;
		
		mat4 modelOriginal;
		bool is3D = false;
		
	public:
		Entity();
		Entity(Renderer renderer);
		~Entity();
		Entity(int newx, int newy, int newz);
		Entity(float newx, float newy, float newz);
		Entity(vec3 pos);
		void setPosition(vec3 pos);
		vec3 getPosition();
		float getX();
		float getY();
		float getZ();
		void setX(float newx);
		void setY(float newy);
		void setZ(float newz);
		void moveTo(float newx, float newy, float newz);
		virtual void set();
		virtual void draw();
		void endDraw();
		void Rotate(vec3 newRotation);
		void Scale(vec3 newScale);
		vec3 GetScale();
		Renderer currentRenderer;
		CollisionManager colMan;
		mat4 model;
	};
}

#endif //ENTITY_H

#pragma warning(pop)