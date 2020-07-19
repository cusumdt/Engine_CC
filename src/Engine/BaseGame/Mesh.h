#ifndef MESH_H
#define MESH_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "Shader.h"
#include <vector>
#include <string>

#define LIMIT_TEXTURE 8

using namespace std;

namespace Engine
{
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
	public:
		int layer;
		unsigned int VAO;
		vector<unsigned int> indices;
		vector<Vertex> vertices;
		vector<Texture> textures;
	private:
		void SetupMesh();
	public:
		Mesh(){};
		Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures, int _layer);
		void Draw(Shader shader);
	};
}

#endif //MESH_H
