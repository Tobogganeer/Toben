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

#include <sstream>

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
    
    Shader shader = Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
    Texture tex = Texture("res/textures/test2.png");

    HeapRef<Mesh> mesh = Mesh::Create(verts, indices);
    HeapRef<Material> mat = Material::Create(shader, tex);

    MeshRenderer rend = MeshRenderer(mesh, mat);

    GLFWwindow* window = Display::GetWindow();
    Graphics::Init(window);

    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        Graphics::Clear();

        Graphics::Draw(rend);

        Graphics::PostRender();
    }

    return 0;
}