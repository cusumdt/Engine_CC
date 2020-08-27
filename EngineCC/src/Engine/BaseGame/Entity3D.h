#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef ENTITY3D_H
#define ENTITY3D_H
#define DLLEXPORT __declspec(dllexport)

#include "Entity.h"
#include "Material.h"
#include "LightContainer.h"
#include "Model.h"
#include "Shader.h"

#include <deque>
#include <array>

using namespace Graficos1;

namespace Graficos2
{
	struct Bounds
	{
		float maxX = INT32_MIN;
		float maxY = INT32_MIN;
		float maxZ = INT32_MIN;
		float minX = INT32_MAX;
		float minY = INT32_MAX;
		float minZ = INT32_MAX;
	};

	struct VertexArray
	{
		glm::vec3 actualVertexArray[8];
	};

	class DLLEXPORT AABB
	{
	private:
		glm::vec3 vertex[8];
		unsigned int VAO, VBO, EBO;
		std::vector<unsigned int> indices;
		bool isVisible = true;
		Shader boxShader;
	public:
		AABB();
		void set();
		void CalculateBoundingBox(Bounds bounds);
		void CreateBuffers();
		void Setup();
		void Draw(mat4 model);
		glm::vec3 GetVertex(unsigned int index);
	};

	class DLLEXPORT Entity3D : public Entity // Shaders que se van a usar, destruye su shader, bindea shaders
	{
	protected:
		Material texture1;
		Material texture2;
		float red;
		float green;
		float blue;
		float alpha;
		vec3 front;
		vec3 up;
		vec3 right;
		ModelsConfig config;
		int layer;
		vector<Entity3D> parent;
		int childID;
		Model entireModel3D;
		string name;
	public:
		static Entity3D childToGet;
		static Entity3D parentToGet;
		Bounds bounds;
		AABB box;
		AABB resizableBox;
		vector<Entity3D> children;
		Shader shader;
		Model model3D;
		mat4 worldModel;
	public:
		Entity3D();
		~Entity3D();
		void SetParent(Entity3D _parent);
		void AddChild(Entity3D _child);
		Entity3D* GetChild(int index);
		Entity3D* GetChild(string name);
		void MoveForward2Axis(float speed);
		void set(string modelPath, bool flipUVs);
		void setPosition(vec3 _translation);
		void Rotate(vec3 _rotation);
		void Scale(vec3 _scale);
		void setPosition(vec3 _translation,mat4 worldModelParent);
		void Rotate(vec3 _rotation, mat4 worldModelParent);
		void Scale(vec3 _scale, mat4 worldModelParent);
		void UpdateModelMatrix(mat4 worldMatrix);
		Bounds UpdateModelMatrixAndBoundingBox(mat4 worldMatrix);
		void draw();
		void SetTexture(int childLayer, int meshIndex, string type, string path);
		void SetMaterial2(const char* path, GLuint type, bool flip, GLint FilteringOption);
		mat4* GetWorldModel();
		void CalculateBounds(vector<Vertex> vertices);
		Bounds CombineBounds(Bounds bounds1, Bounds bounds2);
		Bounds GenerateBoundsByVertex(VertexArray vertexArray);
		Bounds GenerateBoundsByTransformedVertex(VertexArray vArray, glm::mat4 modelMatrix);
		AABB GetAABB();
		Entity3D SetDefaultParameters(Entity3D entity);
		//inline gets
		inline GLuint GetShader() { return shader.ID; }
		inline vec3 GetFront() { return front; }
		inline vec3 GetUp() { return up; }
		inline vec3 GetRight() { return front; }
		inline vec3 GetRotation() { return rotation; }
	};

	
}

#endif //ENTITY3D_H

#pragma warning(pop)