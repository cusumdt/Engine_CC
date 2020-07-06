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
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include "BdB.h"
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
unsigned int TextureFromFile(string path, bool gamma = false);

namespace Engine3D
{

	class DLLEXPORT Model
	{
	private:
		vec3 boundingBoxMin;
		vec3 boundingBoxMax;
		ModelsConfig config;
		vector<Mesh> meshes;
		vector<Texture> textures_loaded;
		string directory;
		void loadModel(string path, bool flipUVs, mat4 model);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			string typeName);
		void GenerateBoundingBox();

	public:
		Model();
		int currentLayer;
		Shader shader;
		void SetMeshTexture(int meshIndex, Texture newTexture);
		void SetModel(string path, bool flipUVs, mat4 model, ModelsConfig config);
		void Draw(mat4 model);
		vector<Mesh> GetMeshes();
	}; 
}

#endif //MODEL_H