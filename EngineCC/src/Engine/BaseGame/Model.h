#pragma warning(push)

#pragma warning(disable:4251) //Desactivando los warnings de DLL-Interface.

#ifndef MODEL_H
#define MODEL_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "Mesh.h"
#include "Importer.h"
#include "Material.h"
#include "Shader.h"
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
unsigned int TextureFromFile(string path, bool gamma = false);

namespace Graficos2
{

	class DLLEXPORT Model
	{
	private:
		vector<Mesh> meshes;
		vector<string> names;
		vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		string directory;
	private:
		void loadModel(string path, bool flipUVs, mat4 model);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	public:
		Model();
		bool isNull;
		int currentLayer;
		Shader shader;
		void SetMeshTexture(int meshIndex, Texture newTexture);
		void SetModel(string path, bool flipUVs, mat4 model);
		void Draw(mat4 model);
		void EmptyMeshes();
		void AddMesh(Mesh mesh);
		inline vector<Mesh> GetMeshes() { return meshes; }
		inline vector<string> GetNames() { return names; }
	}; 
}

#endif //MODEL_H

#pragma warning(pop)