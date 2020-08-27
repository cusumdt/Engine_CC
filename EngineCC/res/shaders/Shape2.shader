#shader vertex
#version 330 core

layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

void main(){
    // El color de cada vértice será interpolado
    // para producir el color de cada fragmento
    fragmentColor = vertexColor;
}

#shader fragment
#version 330 core

in vec3 fragmentColor;


void main()
{
	color = fragmentColor;
};