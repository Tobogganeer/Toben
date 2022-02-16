#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "MeshRenderer.h"

#pragma region GL Errors

#define GL_DEBUG

#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef GL_DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

static void GLClearError()
{
    //while (glGetError() != GL_NO_ERROR);

    while (GLenum error = glGetError())
    {
        std::cout << "[P.OpenGL Error]: " << error << std::endl;
    }
}

static bool GLLogCall(const char* func, const char* file, int line)
{
    bool success = true;

    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: " << "(" << error << "): " << func << " - " << file << ":" << line << std::endl;
        success = false;
    }

    return success;
}

#pragma endregion

class Graphics
{
public:
    static void Init(GLFWwindow* window);
    static void Clear();
    static void Draw(const MeshRenderer& meshRenderer);
    static void PostRender();
private:
    static GLFWwindow* window;
};

