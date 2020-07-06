#include "Material.h"

using namespace Engine;

Material::Material()
{
	texture = 0;
}

Material::~Material()
{

}

void Material::SetTexture(const char* path, GLuint type, bool flip,GLint FilteringOption)
{
	stbi_set_flip_vertically_on_load(flip);

	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	unsigned int newTexture;
	
	glGenTextures(1, &newTexture);
	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, newTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilteringOption);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilteringOption);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	
	texture = newTexture;
}

unsigned int Material::GetTexture()
{
	return texture;
}