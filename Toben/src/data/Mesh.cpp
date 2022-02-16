#include "Mesh.h"
#include "../graphics/Graphics.h"

Mesh::Mesh(HeapRef<std::vector<Vertex>> vertices, HeapRef<std::vector<unsigned int>> indices)
	:vertices(vertices), indices(indices)
{
	GLCall(vao = HeapRef<VAO>(new VAO()));
	GLCall(vbo = HeapRef<VBO>(new VBO(vertices->data(), sizeof(Vertex) * vertices->size())));

	BufferLayout layout;
	layout.Push<glm::vec3>(1);
	layout.Push<glm::vec3>(1);
	layout.Push<glm::u16vec2>(1);
	layout.Push<glm::u8vec4>(1);
	GLCall(vao->Add(vbo, layout));

	GLCall(ibo = HeapRef<IBO>(new IBO(indices->data(), indices->size())));
}

void Mesh::Load()
{
	vao->Bind();
	ibo->Bind();
}

void Mesh::Unload()
{
	vao->Unbind();
	ibo->Unbind();
}
/*

glm::vec3 position;
glm::vec3 normal;
glm::u16vec2 uv;
glm::u8vec4 colour;

*/

Mesh::~Mesh()
{

}

HeapRef<Mesh> Mesh::Create(HeapRef<std::vector<Vertex>> vertices, HeapRef<std::vector<unsigned int>> indices)
{
	return HeapRef<Mesh>(new Mesh(vertices, indices));
}