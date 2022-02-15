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
#include "utils/HeapData.h"
#include "graphics/Graphics.h"

//https://github.com/g-truc/glm/blob/master/manual.md#section1
//https://github.com/g-truc/glm
//https://github.com/nothings/stb


int main(void)
{
    Display display;
    if (!display.Create(1280, 720, "Toben", false)) return -1;

    HeapRef<std::vector<Vertex>> verts(new std::vector<Vertex>
        ({
            Vertex({-0.5f, -0.5f, 0.0f}, {0, 0, 0}, {0, 0}),
            Vertex({ 0.5f, -0.5f, 0.0f}, {0, 0, 0}, {1, 0}),
            Vertex({ 0.5f,  0.5f, 0.0f}, {0, 0, 0}, {1, 1}),
            Vertex({-0.5f,  0.5f, 0.0f}, {0, 0, 0}, {0, 1}),
        }));
    
    HeapRef<std::vector<unsigned int>> indices(new std::vector<unsigned int>
        ({
            0, 1, 2,
            2, 3, 0
        }));
    
    GLCall(HeapRef<Mesh> mesh = HeapRef<Mesh>(new Mesh(verts, indices)));

    Shader shader = Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
    shader.Bind();

    Texture tex = Texture("res/textures/test2.png");
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

        mesh->Load();

        GLenum mode = GL_TRIANGLES;
        //GLCall(glDrawElements(mode, indices->size(), GL_UNSIGNED_INT, nullptr));
        GLCall(glDrawElements(mode, mesh->indices->size(), GL_UNSIGNED_INT, nullptr));

        //mesh.Unload();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}