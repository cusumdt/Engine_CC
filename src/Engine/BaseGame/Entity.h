#pragma warning(push)

#pragma warning(disable:4251)

#ifndef ENTITY_H
#define ENTITY_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "CollisionManager.h"
#include "CustomVector.h"

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
		Entity(int _x, int _y, int _z);
		Entity(float _x, float _y, float _z);
		Entity(vec3 _pos);

		virtual void Set(){};
		virtual void Draw(){};
		void EndDraw();

		void MoveTo(float _x, float _y, float _z);
		void Rotate(vec3 _rotation);
		void Scale(vec3 _scale);

		inline vec3 GetScale() { return scale; }
		inline vec3 GetPosition() { return position; }
		inline float GetX() { return position.x; }
		inline float GetY() { return position.y; }
		inline float GetZ(){ return position.z; }
		inline void SetX(float _x) { position.x = _x; }
		inline void SetY(float _y){ position.y = _y; }
		inline void SetZ(float _z){ position.z = _z; }
		void SetPosition(vec3 _pos);

		Renderer currentRenderer;
		CollisionManager colMan;
		mat4 model;
	};
}

#endif //ENTITY_H

#pragma warning(pop)