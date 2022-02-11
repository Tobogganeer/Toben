#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include "glm/vec3.hpp"
#include "tobutils/Time.h"
#include "data/Shader.h"

#define GL_DEBUG

#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef GL_DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

//https://github.com/g-truc/glm/blob/master/manual.md#section1
//https://github.com/g-truc/glm
//https://github.com/nothings/stb


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
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

static void glErrorCallback(int error, const char* description)
{
    fprintf(stderr, "[OpenGL Error]: %s\n", description);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwSetErrorCallback(glErrorCallback);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Toben", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error Initializing GLEW!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float positions[8] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f, // 3
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


    Shader shader = Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
    shader.Use();

    //glBindBuffer(GL_ARRAY_BUFFER, 0);


    Time::Init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

        GLenum mode = GL_TRIANGLES;
        GLCall(glDrawElements(mode, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.Delete();

    glfwTerminate();
    return 0;
}