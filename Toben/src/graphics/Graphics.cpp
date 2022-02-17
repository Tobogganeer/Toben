#include "Graphics.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/vec3.hpp"
#include "../vendor/glm/mat4x4.hpp"
// JUST FOR DEBUG ^^^

GLFWwindow* Graphics::window;

void Graphics::Init(GLFWwindow* window)
{
	Graphics::window = window;
}

void Graphics::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
}

void Graphics::YuckyYuckUploadMatrix(const MeshRenderer& mesh, Camera& cam, Transform& transform)
{
	mesh.Load();

	glm::mat4 mvp = cam.projMatrix * cam.viewMatrix * transform.modelMatrix;

	mesh.material->shader.SetMat4("mvp", mvp);

	GLenum mode = GL_TRIANGLES;
	GLCall(glDrawElements(mode, mesh.mesh->indices->size(), GL_UNSIGNED_INT, nullptr));

	mesh.Unload();
}

void Graphics::Draw(const MeshRenderer& meshRenderer)
{
	meshRenderer.Load();

	// Load matrices
	
	GLenum mode = GL_TRIANGLES;
	GLCall(glDrawElements(mode, meshRenderer.mesh->indices->size(), GL_UNSIGNED_INT, nullptr));

	meshRenderer.Unload();
}

void Graphics::PostRender()
{
	glfwSwapBuffers(window);

	glfwPollEvents();
}