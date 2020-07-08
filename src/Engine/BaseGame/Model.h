#ifndef MODEL_H
#define MODEL_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "Mesh.h"
#include "Importer.h"
#include "Material.h"
#include "Shader.h"
//#include "BdB.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>

#define BOX_VERTEX 8

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
unsigned int TextureFromFile(string path, bool gamma = false);

namespace Engine
{

	class DLLEXPORT Model
	{
	private:

		SpecularMode config;
		vector<Mesh> meshObjects;
		vector<Texture> textures_loaded;
		string directory;
		void loadModel(string path, bool flipUVs, mat4 model);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			string typeName);
		void GenerateBoundingBox();

	public:
		Model(){};
		int currentLayer;
		Shader shader;
		void SetMeshTexture(int meshIndex, Texture newTexture);
		void SetModel(string path, bool flipUVs, mat4 model, SpecularMode config);
		void Draw(mat4 model);
		vector<Mesh> GetMeshes();
		vec3 boundingBoxMin;
		vec3 boundingBoxMax;
	}; 
}

#endif //MODEL_H