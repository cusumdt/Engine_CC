#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.


#ifndef ENTITY_H
#define ENTITY_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "CollisionManager.h"

namespace Graficos1
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
		Renderer currentRenderer;
		CollisionManager colMan;
		mat4 model;
	public:
		Entity();
		Entity(Renderer renderer);
		~Entity();
		Entity(int _x, int _y, int _z);
		Entity(float _x, float _y, float _z);
		Entity(vec3 pos);
		virtual void setPosition(vec3 _translation);
		void setX(float _x);
		void setY(float _y);
		void setZ(float _z);
		void moveTo(float _x, float _y, float _z);
		virtual void set();
		virtual void draw();
		void endDraw();
		virtual void Rotate(vec3 _rotation);
		virtual void Scale(vec3 _scale);
		//Inline gets
		inline vec3 GetScale() { return scale; }
		inline vec3 getPosition() { return position; }
		inline float getX() { return position.x; }
		inline float getY() { return position.y; }
		inline float getZ() { return position.z; }
	};
}

#endif //ENTITY_H

#pragma warning(pop)