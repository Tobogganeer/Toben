#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include "vendor/glm/vec3.hpp"
#include "utils/Time.h"
#include "data/Shader.h"
#include "data/Texture.h"
#include "graphics/Display.h"
#include "data/buffers/Buffers.h"
#include "utils/normalize.h"
#include "data/Vertex.h"
#include "data/Mesh.h"

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

int main(void)
{
    Display display;
    if (!display.Create(1280, 720, "Toben", false)) return -1;

    std::vector<Vertex> verts = std::vector<Vertex>
        ({
            Vertex({-0.5f, -0.5f, 0.0f}, {0, 0, 0}, {0, 0}),
            Vertex({ 0.5f, -0.5f, 0.0f}, {0, 0, 0}, {1, 0}),
            Vertex({ 0.5f,  0.5f, 0.0f}, {0, 0, 0}, {1, 1}),
            Vertex({-0.5f,  0.5f, 0.0f}, {0, 0, 0}, {0, 1}),
        });
    
    std::vector<unsigned int> indices = std::vector<unsigned int>
        ({
            0, 1, 2,
            2, 3, 0
        });
    
    Mesh mesh = Mesh(verts, indices);

    //verts[0].Print();
    //verts[1].Print();
    //verts[2].Print();
    //verts[3].Print();
    //
    //std::cout << sizeof(Vertex) << std::endl;
    //
    //std::cin.get();

    
    //float positions[8] = {
    //    -0.5f, -0.5f, // 0
    //     0.5f, -0.5f, // 1
    //     0.5f,  0.5f, // 2
    //    -0.5f,  0.5f, // 3
    //};
    //
    //unsigned int indices[6] = {
    //    0, 1, 2,
    //    2, 3, 0
    //};
    //
    //VAO vao;
    //VBO vbo = VBO(positions, 4 * 2 * sizeof(float));
    //
    //BufferLayout layout;
    //layout.Push<float>(2);
    //vao.Add(vbo, layout);
    //
    //IBO ibo = IBO(indices, 2 * 3);

    //VAO vao = VAO();
    //VBO vbo = VBO(verts.data(), sizeof(Vertex) * verts.size());
    //
    //BufferLayout layout;
    //layout.Push<glm::vec3>(1);
    //layout.Push<glm::vec3>(1);
    //layout.Push<glm::u16vec2>(1);
    //layout.Push<glm::u8vec4>(1);
    //vao.Add(vbo, layout);
    //
    //IBO ibo = IBO(indices.data(), indices.size());
    

    Shader shader = Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
    shader.Bind();

    Texture tex = Texture("res/textures/test.png");
    tex.Bind();

    shader.SetTexture("mainTex", 0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLFWwindow* window = Display::GetWindow();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

        //vao.Bind();
        //ibo.Bind();

        mesh.Load();

        GLenum mode = GL_TRIANGLES;
        //GLCall(glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, nullptr));
        GLCall(glDrawElements(mode, mesh.indices.size(), GL_UNSIGNED_INT, nullptr));

        mesh.Unload();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}