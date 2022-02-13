#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
	:vertices(vertices), indices(indices)
{
	vao = VAO();
	vbo = VBO(vertices.data(), sizeof(Vertex) * vertices.size());

	BufferLayout layout;
	layout.Push<glm::vec3>(1);
	layout.Push<glm::vec3>(1);
	layout.Push<glm::u16vec2>(1);
	layout.Push<glm::u8vec4>(1);
	vao.Add(vbo, layout);

	ibo = IBO(indices.data(), indices.size());
}

void Mesh::Load()
{
	vao.Bind();
	ibo.Bind();
}

void Mesh::Unload()
{
	vao.Unbind();
	ibo.Unbind();
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
