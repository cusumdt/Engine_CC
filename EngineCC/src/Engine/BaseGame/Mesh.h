#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef MESH_H
#define MESH_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "Shader.h"
#include <vector>
#include <string>

using namespace std;

namespace Graficos2
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
	private:
		void SetupMesh();
	public:
		int layer;
		unsigned int VAO;
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
	public:
		Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures, int _layer);
		Mesh();
		void SetMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void Draw(Shader shader);
	};
}

#endif //MESH_H

#pragma warning(pop)