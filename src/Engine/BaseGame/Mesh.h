#ifndef MESH_H
#define MESH_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "Shader.h"
#include <vector>
#include <string>

using namespace std;

namespace Engine
{

	enum class ModelsConfig
	{
		A,
		B,
		maxConfigs
	};

	struct Vertex
	{
	
		vec3 Position;
		vec3 Normal;
		vec2 TexCoords;
		vec3 Tangent;
		vec3 Bitangent;
	};

	struct Texture
	{
		unsigned int id;
		string type;
		string path; 
	};

	class DLLEXPORT Mesh
	{
	private:
		unsigned int VBO;
		unsigned int EBO;
		void SetupMesh();
	public:
		int layer;
		unsigned int VAO;
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		Mesh() {};
		void Draw(Shader shader, ModelsConfig config);
	};
}

#endif //MESH_H
