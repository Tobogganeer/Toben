#include "Graphics.h"

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