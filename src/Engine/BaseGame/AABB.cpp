#include "Entity3D.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"


AABB::AABB()
{
}
void AABB::set()
{
	ShaderProgramSource source = Shader::ShaderParser("res/shaders/Shape.shader");
	boxShader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);

	GLushort cubeIndices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};
	for (int i = 0; i < 36; i++)
		indices.push_back(cubeIndices[i]);
	isVisible = true;

	CreateBuffers();
	Setup();
}


void AABB::CalculateBoundingBox(Bounds bounds)
{
	glm::vec3 boundingBoxVertex[8] =
	{
		glm::vec3(bounds.minX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.minZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.minZ),
	};

	for (int i = 0; i < 8; i++)
		vertex[i] = glm::vec4(boundingBoxVertex[i], 1.f);

	Setup();
}

void AABB::CreateBuffers()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void AABB::Setup()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void AABB::Draw(mat4 model)
{
	boxShader.use();
	glBindVertexArray(VAO);

	// view/projection transformations
	mat4 proj = BaseGame::_render.GetProjection();
	mat4 view = BaseGame::_render.GetView();

	boxShader.setMat4("model", model);
	boxShader.setMat4("view", view);
	boxShader.setMat4("projection", proj);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(0);
}

glm::vec3 AABB::GetVertex(unsigned index)
{
	return vertex[index];
}
