#include "Model.h"
#include "BaseGame.h"

using namespace Engine;


unsigned int TextureFromFile(string _path, bool _gamma)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrComponents, STBI_rgb_alpha);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << _path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int TextureFromFile(const char* _path, const string& _directory, bool _gamma)
{
	string filename = string(_path);
	filename = _directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, STBI_rgb_alpha);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << _path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Model::loadModel(string _path, bool _flipUVs, mat4 _model)
{
	boundingBoxMin = vec3(INT_MAX, INT_MAX, INT_MAX);
	boundingBoxMax = vec3(INT_MIN, INT_MIN, INT_MIN);
	// Lee el archivo
	Assimp::Importer importer;
	const aiScene* scene;

	if (_flipUVs)
	{
		scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	}
	else
	{
		scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	}

	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = _path.substr(0, _path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);

	// Reordenar Layers (Capas de los nodos)
	list<int> meshesLayers;

	for (int i = 0; i < meshObjects.size(); i++)
	{
		meshesLayers.push_back(meshObjects[i].layer);
	}

	meshesLayers.sort();
	meshesLayers.unique();

	int value = 0;
	int layerValue = 1;

	for (std::list<int>::iterator it = meshesLayers.begin(); it != meshesLayers.end(); it++)
	{
		value = *it;

		for (int j = 0; j < meshObjects.size(); j++)
		{
			if (meshObjects[j].layer == value)
			{
				meshObjects[j].layer = layerValue;
			}
		}

		layerValue++;
	}
}

void Model::processNode(aiNode* _node, const aiScene* _scene)
{
	// Procesa cada mesh alojado en el nodo actual
	for (unsigned int i = 0; i < _node->mNumMeshes; i++)
	{
		// el nodo objeto solo contiene indices para realizar el index del actual meshObjects de la scene. 
		// la scene contiene toda la data, el nodo solo esta para mantener todo en orden (como las relaciones entre nodos).
		aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
		meshObjects.push_back(processMesh(mesh, _scene));
	}

	// una vez procesados todos los meshObjects (si es que hay alguno) procesamos los nodos hijos de manera recursiva.
	for (unsigned int i = 0; i < _node->mNumChildren; i++)
	{
		processNode(_node->mChildren[i], _scene);
	}
}

Mesh Model::processMesh(aiMesh* _mesh, const aiScene* _scene)
{
	// data to fill
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = _mesh->mVertices[i].x;
		vector.y = _mesh->mVertices[i].y;
		vector.z = _mesh->mVertices[i].z;
		vertex.Position = vector;

		// PosBox
	
		if (vertex.Position.x < boundingBoxMin.x)
			boundingBoxMin.x = vertex.Position.x;
		if (vertex.Position.x > boundingBoxMax.x)
			boundingBoxMax.x = vertex.Position.x;
		if (vertex.Position.y < boundingBoxMin.y)
			boundingBoxMin.y = vertex.Position.y;
		if (vertex.Position.y > boundingBoxMax.y)
			boundingBoxMax.y = vertex.Position.y;
		if (vertex.Position.z < boundingBoxMin.z)
			boundingBoxMin.z = vertex.Position.z;
		if (vertex.Position.z > boundingBoxMax.z)
			boundingBoxMax.z = vertex.Position.z;

		// normals
		vector.x = _mesh->mNormals[i].x;
		vector.y = _mesh->mNormals[i].y;
		vector.z = _mesh->mNormals[i].z;
		vertex.Normal = vector;
		// texture coordinates
		if (_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = _mesh->mTextureCoords[0][i].x;
			vec.y = _mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		// tangent
		vector.x = _mesh->mTangents[i].x;
		vector.y = _mesh->mTangents[i].y;
		vector.z = _mesh->mTangents[i].z;
		vertex.Tangent = vector;
		// bitangent
		vector.x = _mesh->mBitangents[i].x;
		vector.y = _mesh->mBitangents[i].y;
		vector.z = _mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. Diffuse maps
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. Specular maps
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. Normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. Height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	// 5. Emmisive maps
	std::vector<Texture> emissionMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emission");
	textures.insert(textures.end(), emissionMaps.begin(), emissionMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* _mat, aiTextureType _type, string _typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++)
	{
		aiString str;
		_mat->GetTexture(_type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = _typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

void Model::GenerateBoundingBox()
{
	float boundingBoxVertices[BOX_VERTEX*3] =
	{
		boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z,
		boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z,
		boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z,
		boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z,
		boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z,
		boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z,
		boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z,
		boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z
	};
	cout << "xMin" << boundingBoxMin.x << endl << "yMin" << boundingBoxMin.y << endl << "zMin" << boundingBoxMin.z << endl<< "xMax" << boundingBoxMax.x <<endl << "yMax" << boundingBoxMax.y << endl << "zMax" << boundingBoxMax.z << endl;
	// Box
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, boundingBoxVertices);

	glDrawArrays(GL_QUADS, 0, 24);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void Model::SetMeshTexture(int _meshIndex, Texture _texture)
{
	textures_loaded.push_back(_texture);
	meshObjects.at(_meshIndex).textures.push_back(_texture);
}

void Model::SetModel(string _path, bool _flipUVs, mat4 _model)
{
	loadModel(_path, _flipUVs, _model);
}

void Model::Draw(mat4 _model)
{
	shader.use();

	// view/projection transformations
	mat4 proj = BaseGame::_render.GetProjection();
	mat4 view = BaseGame::_render.GetView();

	shader.setMat4("model", _model);
	shader.setMat4("view", view);
	shader.setMat4("projection", proj);

	for (unsigned int i = 0; i < meshObjects.size(); i++)
		meshObjects[i].Draw(shader);

	GenerateBoundingBox();

}






