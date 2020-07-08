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

unsigned int TextureFromFile(string _path, bool _gamma=false);
unsigned int TextureFromFile(const char* _path, const string& _directory, bool _gamma = false);

namespace Engine
{
	class DLLEXPORT Model
	{
	private:
		SpecularMode config;
		vector<Mesh> meshObjects;
		vector<Texture> textures_loaded;
		string directory;

	private:
		void loadModel(string _path, bool _flipUVs, mat4 _model);
		void processNode(aiNode* _node, const aiScene* _scene);
		Mesh processMesh(aiMesh* _mesh, const aiScene* _scene);
		vector<Texture> loadMaterialTextures(aiMaterial* _mat, aiTextureType _type, string _typeName);
		void GenerateBoundingBox();

	public:
		int currentLayer;
		Shader shader;
		vec3 boundingBoxMin;
		vec3 boundingBoxMax;

	public:
		Model():boundingBoxMax(0),boundingBoxMin(0),config(SpecularMode::ONE),currentLayer(0){};
		void SetMeshTexture(int _meshIndex, Texture _texture);
		void SetModel(string _path, bool _flipUVs, mat4 _model, SpecularMode _config);
		inline vector<Mesh> GetMeshes() {return meshObjects;}
		void Draw(mat4 _model);
		
	}; 
}

#endif //MODEL_H