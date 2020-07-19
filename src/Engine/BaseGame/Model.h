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
		vector<Mesh> meshObjects;
		vector<string> names;
		vector<Texture> textures_loaded;
		string directory;

	private:
		void loadModel(string _path, bool _flipUVs, mat4 _model);
		void processNode(aiNode* _node, const aiScene* _scene);
		Mesh processMesh(aiMesh* _mesh, const aiScene* _scene);
		vector<Texture> loadMaterialTextures(aiMaterial* _mat, aiTextureType _type, string _typeName);
		void GenerateBoundingBox();

	public:
		Shader shader;
		vec3 boundingBoxMin;
		vec3 boundingBoxMax;
		bool isNull;
		int currentLayer;

	public:
		Model():boundingBoxMax(0),boundingBoxMin(0),isNull(true){};
		void SetMeshTexture(int _meshIndex, Texture _texture);
		void SetModel(string _path, bool _flipUVs, mat4 _model);
		void Draw(mat4 _model);
		void EmptyMeshes();
		void AddMesh(Mesh mesh);
		inline vector<Mesh> GetMeshes() { return meshObjects; }
		inline vector<string> GetNames() { return names; }
	}; 
}

#endif //MODEL_H