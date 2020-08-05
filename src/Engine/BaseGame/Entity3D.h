#ifndef ENTITY3D_H
#define ENTITY3D_H
#define DLLEXPORT __declspec(dllexport)

#include "Entity.h"
#include "Material.h"
#include "Light.h"
#include "Model.h"
#include "Shader.h"
#include <deque>
#include <array>

using namespace Engine;

namespace Engine
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

	class DLLEXPORT BoundingBox
	{
		glm::vec3 vertex[8];
		unsigned int VAO, VBO, EBO;
		std::vector<unsigned int> indices;
		bool isVisible = true;
		Shader boxShader;

	public:
		BoundingBox();
		void set();
		void CalculateBoundingBox(Bounds bounds);
		void CreateBuffers();
		void Setup();
		void Draw(mat4 model);
		glm::vec3 GetVertex(unsigned int index);
	};
	
	class DLLEXPORT Entity3D : public Entity
	{
	protected:
		int layer;
		int childID;
		float red;
		float green;
		float blue;
		float alpha;
		vec3 front;
		vec3 up;
		vec3 right;
		string name;
		Material texture1;
		Material texture2;
		Model entireModel3D;
		vector<Entity3D> parent;
	public:
		Shader shader;
		BoundingBox box;
		BoundingBox resizableBox;
		Bounds bounds;
		vec3 boundingBoxMin;
		vec3 boundingBoxMax;
		Model model3D;
		mat4 worldModel;
		vector<Entity3D> children;
		static Entity3D childToGet;
		static Entity3D parentToGet;
		
	public:
		Entity3D();
		~Entity3D();

		void MoveForward2Axis(float speed);
		void Draw();

		void Set(string modelPath, bool flipUVs);
		void SetTexture(int childLayer, int meshIndex, string type, string path);
		void SetMaterial(const char* path, GLuint type, bool flip, GLint FilteringOption);
		void SetParent(Entity3D newParent);

		inline GLuint GetShader(){return shader.ID;}
		inline vec3 GetFront() { return front; }
		inline vec3 GetUp() { return up; }
		inline vec3 GetRight() { return right; }
		inline vec3 GetRotation() { return rotation; }

		//Nuevo
		void AddChild(Entity3D _child);
		Entity3D* GetChild(int _index);
		Entity3D* GetChild(string name);
		inline mat4* GetWorldModel() { return &worldModel; };
		inline BoundingBox GetAABB() { return box; }
		void setPosition(vec3 translation);
		void Rotate(vec3 _rotation);
		void Scale(vec3 _scale);
		void setPosition(vec3 _translation, mat4 worldModelParent);
		void Rotate(vec3 _rotation, mat4 worldModelParent);
		void Scale(vec3 _scale, mat4 worldModelParent);
		void UpdateModelMatrix(mat4 worldMatrix);
		Bounds UpdateModelMatrixAndBoundingBox(mat4 worldMatrix);
		void CalculateBounds(vector<Vertex> vertices);
		Bounds CombineBounds(Bounds bounds1, Bounds bounds2);
		Bounds GenerateBoundsByVertex(VertexArray vertexArray);
		Bounds GenerateBoundsByTransformedVertex(VertexArray vArray, glm::mat4 modelMatrix);
		
		Entity3D SetDefaultParameters(Entity3D entity);
	};
}

#endif //ENTITY3D_H
