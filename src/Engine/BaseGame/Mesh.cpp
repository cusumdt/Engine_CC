#include "Mesh.h"
#include "BaseGame.h"


using namespace Engine;

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures, int _layer)
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;
	layer = _layer;
	SetupMesh();
}

void Mesh::SetupMesh()
{
	// crea los buffers y arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// carga la data de los vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//El efecto es que simplemente podemos pasar un puntero a la estructura y se 
	//traduce perfectamente en una matriz glm :: vec3 / 2 
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Setea los Vertex Atribbute Pointers
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
	// enlaza la textura adecuada
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	unsigned int emissionNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		// activa la unidad de textura adecuada antes de la uni�n
		// recupera el n�mero de textura (la N en diffuse_textureN)
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
			number = std::to_string(normalNr++);
			shader.setInt("material.normal", i);
		}
		else if (name == "texture_height")
		{
			number = std::to_string(heightNr++);
			shader.setInt("material.height", i);
		}
		else if (name == "texture_emission")
		{
			number = std::to_string(emissionNr++);
			shader.setInt("material.emission", i);
		}

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	if (diffuseNr <= 1)
		shader.setInt("material.diffuse", LIMIT_TEXTURE);
	
	if (specularNr <= 1)
		shader.setInt("material.specular", LIMIT_TEXTURE);

	if (normalNr <= 1)
		shader.setInt("material.normal", LIMIT_TEXTURE);

	if (heightNr <= 1)
		shader.setInt("material.height", LIMIT_TEXTURE);

	if (emissionNr <= 1)
		shader.setInt("material.emission", LIMIT_TEXTURE);

	//En caso de que no haya un valor de brillo, establece uno.
	glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), 16.0f);

	// Dibuja la mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// siempre es una buena pr�ctica restablecer todo a los valores predeterminados una vez finalizada la configuraci�n.
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}