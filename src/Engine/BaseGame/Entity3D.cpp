#include "Entity3D.h"
#include "BaseGame.h"
#include "Shader.h"
using namespace Engine;
using namespace Engine;

Entity3D::Entity3D()
	:
	boundingBoxMin(0),
	boundingBoxMax(0),
	layer(0),
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
	SetPosition(vec3(GetPosition().x + speed * glm::cos((GetRotation().y - 90) * glm::pi<float>() / 180), GetPosition().y, GetPosition().z - speed * (glm::sin((GetRotation().y - 90) * glm::pi<float>() / 180))));
}
void Entity3D::Draw(bool wireframeActive)
{
	if (wireframeActive) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		model3D.Draw(model);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	model3D.Draw(model);
}

void Entity3D::Set(string modelPath, Color color, bool flipUVs, Light light)
{
	if (light.exists)
	{
		shader=light.shader;
		model3D.shader = shader;
	}
	else
	{
		ShaderProgramSource source = Shader::ShaderParser("res/shaders/3dmodel.shader");
		shader.ID = Shader::CreateShader(source.vertexSource, source.fragmentSource);
		model3D.shader = shader;
	}

	model3D.SetModel(modelPath, flipUVs, model);

	vector<Mesh> meshObjects = model3D.GetMeshes();
	deque<Entity3D> entities;
	deque<Entity3D> entities2;
	deque<Entity3D> entities3;

	for (int i = 0; i < meshObjects.size(); i++)
	{
		Entity3D child;
		child.layer = meshObjects[i].layer;
		entities.push_back(child);
	}

	for (int i = entities.size() - 1; i >= 0; i--)
	{
		if (entities.at(i).layer > 1)
		{
			for (int c = i - 1; c >= 0; c--)
			{
				if (entities.at(c).layer == entities.at(i).layer - 1)
				{
					entities.at(i).SetParent(entities.at(c));
					entities.at(c).children.push_front(entities.at(i));
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
		children.push_back(entities2.at(i));
	}
	boundingBoxMin = model3D.boundingBoxMin;
	boundingBoxMax = model3D.boundingBoxMax;
}
void Entity3D::SetParent(Entity3D _parent)
{
	parent.push_back(_parent);
}
void Entity3D::SetTexture(int meshIndex, string type, string path)
{
	Texture _texture;
	_texture.id = TextureFromFile(path,false);
	_texture.type = type;
	_texture.path = path;

	model3D.SetMeshTexture(meshIndex, _texture);
}
void Entity3D::SetMaterial(const char* path, GLuint type, bool flip, GLint FilteringOption)
{
	texture2.SetTexture(path, type, flip, FilteringOption);
}



