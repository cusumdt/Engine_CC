#include "Mesh.h"
#include "BaseGame.h"

using namespace Graficos1;
using namespace Graficos2;

Mesh::Mesh()
{
}

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures, int _layer) :
	vertices(_vertices),
	indices(_indices),
	textures(_textures),
	layer(_layer)
{
	SetupMesh();
}

void Mesh::SetMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	/*this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	SetupMesh();*/
}

void Mesh::SetupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader shader)
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	unsigned int emissionNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;// shader.setInt("material.diffuse", 0);

		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
			shader.setInt("material.diffuse", i);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++); // transfer unsigned int to stream
			shader.setInt("material.specular", i);
		}
		else if (name == "texture_normal")
		{
			number = std::to_string(normalNr++); // transfer unsigned int to stream
			//shader.setInt("material.emission", 5);
		}
		else if (name == "texture_height")
		{
			number = std::to_string(heightNr++); // transfer unsigned int to stream
			//shader.setInt("material.emission", 5);
		}
		else if (name == "texture_emission")
		{
			number = std::to_string(emissionNr++); // transfer unsigned int to stream
			shader.setInt("material.emission", i);
		}

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	if (diffuseNr <= 1)
	{
		shader.setInt("material.diffuse", 15);
	}

	if (specularNr <= 1)
	{
		shader.setInt("material.specular", 15);
	}

	if (normalNr <= 1)
	{
		//shader.setInt("material.diffuse", -1);
	}

	if (heightNr <= 1)
	{
		//shader.setInt("material.diffuse", -1);
	}

	if (emissionNr <= 1)
	{
		shader.setInt("material.emission", 15);
	}


	// set a default sininess value in case there is none
	glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), 16.0f);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}