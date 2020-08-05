#include "Entity3D.h"
#include "BaseGame.h"
#include "Shader.h"
using namespace Engine;

Entity3D::Entity3D()
	:
	boundingBoxMin(0),
	boundingBoxMax(0),
	red(0),
	green(0),
	blue(0),
	alpha(0),
	front(VECTOR_FRONT),
	up(VECTOR_UP),
	right(VECTOR_LEFT)
{
	_3D = true;
}

Entity3D::~Entity3D()
{
	Shader::DeleteShader(shader.ID);
}

void Entity3D::MoveForward2Axis(float speed)
{
	setPosition(vec3(GetPosition().x + speed * glm::cos((GetRotation().y - 90) * glm::pi<float>() / 180), GetPosition().y, GetPosition().z - speed * (glm::sin((GetRotation().y - 90) * glm::pi<float>() / 180))));
}

void Entity3D::Draw()
{
	if (!model3D.isNull)
	{
		model3D.Draw(worldModel);
		box.Draw(worldModel);

		if (layer == 1)
		{
			UpdateModelMatrixAndBoundingBox(worldModel);
			resizableBox.Draw(worldModel);
		}
	}

	if (children.size() > 0)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children[i].Draw();
		}
	}
}

void Entity3D::Set(string modelPath, bool flipUVs)
{
	if (BaseGame::lightContainer.exists)
	{
		shader = BaseGame::lightContainer.shader;
		entireModel3D.shader = shader;
	}
	else
	{
		ShaderProgramSource source = Shader::ShaderParser("res/shaders/3dmodel.shader");
		shader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);
		entireModel3D.shader = shader;
	}

	entireModel3D.SetModel(modelPath, flipUVs, model);

	//// Children & Parents Config : Esta bien puesta la parentacion pero como usamos memoria estatica cada nodo tiene informacion
	//// vieja y distinta. La unica que mantiene la info actual es el root y sus children, por eso cuando transformamos le pasamos
	//// la worldmatrix actualizada.

	vector<Mesh> meshObjects = entireModel3D.GetMeshes();
	deque<Entity3D> entities;
	deque<Entity3D> entities2;
	std::vector<Entity3D>::iterator it;
	entireModel3D.EmptyMeshes();

	for (int i = 0; i < meshObjects.size(); i++)
	{
		Entity3D newChild;
		newChild.layer = meshObjects[i].layer;
		newChild.model3D.AddMesh(meshObjects[i]);
		newChild.model3D.shader = shader;
		newChild.box.set();
		newChild.resizableBox.set();
		newChild.name = entireModel3D.GetNames().at(i);
		entities.push_back(newChild);
	}

	for (int i = entities.size() - 1; i >= 0; i--)
	{
		entities.at(i).childID = i;

		entities.at(i) = SetDefaultParameters(entities.at(i));


		if (entities.at(i).layer > 1)
		{
			for (int c = i - 1; c >= 0; c--)
			{
				if (entities.at(c).layer == entities.at(i).layer - 1)
				{
					entities.at(i).SetParent(entities.at(c));
					it = entities.at(c).children.begin();
					it = entities.at(c).children.insert(it, entities.at(i));
					entities2.push_front(entities.at(i));
					c = -1;
				}
			}
		}
		else
		{
			entities2.push_front(entities.at(i));
		}
	}

	for (int i = 0; i < entities2.size(); i++)
	{
		if (entities2.at(i).layer == 1)
		{
			children.push_back(entities2.at(i));
		}
	}

	box.set();
	resizableBox.set();
}

void Entity3D::SetParent(Entity3D _parent)
{
	parent.push_back(_parent);
}

void Entity3D::SetTexture(int childLayer, int meshIndex, string type, string path)
{
	Texture _texture;
	_texture.id = TextureFromFile(path,false);
	_texture.type = type;
	_texture.path = path;

	if (!model3D.isNull)
	{
		if (layer == childLayer)
		{
			model3D.SetMeshTexture(meshIndex, _texture);
		}
	}

	if (children.size() > 0)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children[i].layer == childLayer)
			{
				children[i].model3D.SetMeshTexture(meshIndex, _texture);
			}
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children[i].layer != childLayer)
			{
				children[i].SetTexture(childLayer, meshIndex, type, path);
			}
		}
	}
}

void Entity3D::SetMaterial(const char* path, GLuint type, bool flip, GLint FilteringOption)
{
	texture2.SetTexture(path, type, flip, FilteringOption);
}

void Entity3D::AddChild(Entity3D _child)
{
	children.push_back(_child);
}

Entity3D* Entity3D::GetChild(int index)
{
	Entity3D* entityToReturn = nullptr;

	if (children.size() > 0)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children[i].childID == index)
			{
				entityToReturn = &children[i];
			}
		}

		if (entityToReturn == nullptr)
		{
			for (unsigned int i = 0; i < children.size(); i++)
			{
				entityToReturn = children[i].GetChild(index);
				if (entityToReturn != nullptr)
				{
					break;
				}
			}
		}

	}

	return entityToReturn;
}

Entity3D* Entity3D::GetChild(string name)
{
	Entity3D* entityToReturn = nullptr;

	if (children.size() > 0)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children[i].name == name)
			{
				entityToReturn = &children[i];
			}
		}

		if (entityToReturn == nullptr)
		{
			for (unsigned int i = 0; i < children.size(); i++)
			{
				entityToReturn = children[i].GetChild(name);
				if (entityToReturn != nullptr)
				{
					break;
				}
			}
		}

	}

	return entityToReturn;
}

void Entity3D::setPosition(vec3 _translation)
{
	mat4 tempModel = modelOriginal;
	model = glm::translate(tempModel, _translation);
	
	position = _translation;
	UpdateModelMatrixAndBoundingBox(model);
}

void Entity3D::Rotate(vec3 _rotation)
{
	int testID = childID;

	model = glm::rotate(model, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));

	rotation += _rotation;
	UpdateModelMatrixAndBoundingBox(model);
}

void Entity3D::Scale(vec3 _scale)
{
	model = glm::scale(model, _scale);

	scale *= _scale;
	UpdateModelMatrixAndBoundingBox(model);
}

void Entity3D::setPosition(vec3 _translation, mat4 worldModelParent)
{
	model = glm::translate(model, _translation);

	position = _translation;
	UpdateModelMatrixAndBoundingBox(worldModelParent);
}

void Entity3D::Rotate(vec3 _rotation, mat4 worldModelParent)
{
	model = glm::rotate(model, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));

	rotation += _rotation;
	UpdateModelMatrixAndBoundingBox(worldModelParent);
}

void Entity3D::Scale(vec3 _scale, mat4 worldModelParent)
{
	model = glm::scale(model, _scale);

	scale *= _scale;
	UpdateModelMatrixAndBoundingBox(worldModelParent);
}

void Entity3D::UpdateModelMatrix(mat4 worldMatrix)
{
	if (parent.size() > 0 || layer == 1)
	{
		worldModel = worldMatrix * model;
	}
	else
	{
		worldModel = worldMatrix;
	}

	if (children.size() > 0)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children[i].UpdateModelMatrix(this->worldModel);
		}
	}
}

Bounds Entity3D::UpdateModelMatrixAndBoundingBox(mat4 worldMatrix)
{
	if (parent.size() > 0 || layer == 1)
	{
		worldModel = worldMatrix * model;
	}
	else
	{
		worldModel = worldMatrix;
	}

	Bounds cBounds;
	Bounds resultantBounds;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		cBounds = CombineBounds(children[i].UpdateModelMatrixAndBoundingBox(this->worldModel), cBounds);
	}

	VertexArray vertexArray;

	for (int i = 0; i < 8; i++)
	{
		vertexArray.actualVertexArray[i] = box.GetVertex(i);
	}

	bounds = GenerateBoundsByTransformedVertex(vertexArray, model);

	resultantBounds = CombineBounds(cBounds, bounds);

	for (int i = model3D.GetMeshes().size() - 1; i >= 0; i--)
	{
		CalculateBounds(model3D.GetMeshes().at(i).vertices);
	}

	box.CalculateBoundingBox(bounds);
	resizableBox.CalculateBoundingBox(resultantBounds);

	return resultantBounds;
}

void Entity3D::CalculateBounds(vector<Vertex> vertices)
{

	if (!vertices.empty())
	{
		Bounds resetBounds;
		bounds = resetBounds;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices[i].Position.x < bounds.minX)
				bounds.minX = vertices[i].Position.x;
			if (vertices[i].Position.x > bounds.maxX)
				bounds.maxX = vertices[i].Position.x;
			if (vertices[i].Position.y < bounds.minY)
				bounds.minY = vertices[i].Position.y;
			if (vertices[i].Position.y > bounds.maxY)
				bounds.maxY = vertices[i].Position.y;
			if (vertices[i].Position.z < bounds.minZ)
				bounds.minZ = vertices[i].Position.z;
			if (vertices[i].Position.z > bounds.maxZ)
				bounds.maxZ = vertices[i].Position.z;
		}
	}
}

Bounds Entity3D::CombineBounds(Bounds bounds1, Bounds bounds2)
{
	Bounds newBounds;

	newBounds.minX = bounds1.minX < bounds2.minX ? bounds1.minX : bounds2.minX;
	newBounds.minY = bounds1.minY < bounds2.minY ? bounds1.minY : bounds2.minY;
	newBounds.minZ = bounds1.minZ < bounds2.minZ ? bounds1.minZ : bounds2.minZ;
	newBounds.maxX = bounds1.maxX > bounds2.maxX ? bounds1.maxX : bounds2.maxX;
	newBounds.maxY = bounds1.maxY > bounds2.maxY ? bounds1.maxY : bounds2.maxY;
	newBounds.maxZ = bounds1.maxZ > bounds2.maxZ ? bounds1.maxZ : bounds2.maxZ;

	return newBounds;
}

Bounds Entity3D::GenerateBoundsByVertex(VertexArray vertexArray)
{
	Bounds resetBounds;

	for (int i = 0; i < 8; i++)
	{
		if (vertexArray.actualVertexArray[i].x < resetBounds.minX)
			resetBounds.minX = vertexArray.actualVertexArray[i].x;
		if (vertexArray.actualVertexArray[i].x > resetBounds.maxX)
			resetBounds.maxX = vertexArray.actualVertexArray[i].x;
		if (vertexArray.actualVertexArray[i].y < resetBounds.minY)
			resetBounds.minY = vertexArray.actualVertexArray[i].y;
		if (vertexArray.actualVertexArray[i].y > resetBounds.maxY)
			resetBounds.maxY = vertexArray.actualVertexArray[i].y;
		if (vertexArray.actualVertexArray[i].z < resetBounds.minZ)
			resetBounds.minZ = vertexArray.actualVertexArray[i].z;
		if (vertexArray.actualVertexArray[i].z > resetBounds.maxZ)
			resetBounds.maxZ = vertexArray.actualVertexArray[i].z;
	}

	return resetBounds;
}

Bounds Entity3D::GenerateBoundsByTransformedVertex(VertexArray vArray, glm::mat4 modelMatrix)
{
	vector<glm::vec3> vertexVector;
	for (int i = 0; i < 8; i++)
	{
		vArray.actualVertexArray[i] = modelMatrix * glm::vec4(vArray.actualVertexArray[i], 1.f);
		vertexVector.push_back(vArray.actualVertexArray[i]);
	}

	return GenerateBoundsByVertex(vArray);
}

Entity3D Entity3D::SetDefaultParameters(Entity3D entity)
{
	entity.model3D.isNull = false;

	switch (entity.childID)
	{
	case 3:
		entity.model3D.isNull = true;
		break;
	case 4:
		entity.model3D.isNull = true;
		break;
	case 7:
		entity.model3D.isNull = true;
		break;
	default:
		break;
	}

	return entity;
}

