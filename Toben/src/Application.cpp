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
#include "graphics/Camera.h"
#include "data/Transform.h"

//https://github.com/g-truc/glm/blob/master/manual.md#section1
//https://github.com/g-truc/glm
//https://github.com/nothings/stb

#include <sstream>

int main(void)
{
    Display display;
    if (!display.Create(1280, 720, "Toben", false)) return -1;

    //HeapRef<std::vector<Vertex>> verts(new std::vector<Vertex>
    //    ({
    //        Vertex({-0.5f, -0.5f, 0.0f}, {0, 0, 0}, {0, 0}),
    //        Vertex({ 0.5f, -0.5f, 0.0f}, {0, 0, 0}, {1, 0}),
    //        Vertex({ 0.5f,  0.5f, 0.0f}, {0, 0, 0}, {1, 1}),
    //        Vertex({-0.5f,  0.5f, 0.0f}, {0, 0, 0}, {0, 1}),
    //    }));
    //
    //HeapRef<std::vector<unsigned int>> indices(new std::vector<unsigned int>
    //    ({
    //        0, 1, 2,
    //        2, 3, 0
    //    }));

    // wed night 12:05am throwing in the towel i gotta work on presentation

    HeapRef<std::vector<Vertex>> verts(new std::vector<Vertex>
        ({
            Vertex({-0.5f, 0.5f, -0.5f,}, {0, 0, 0},    {0, 0,}),
            Vertex({-0.5f, -0.5f, -0.5f,}, {0, 0, 0},   {0, 1,}),
            Vertex({0.5f, -0.5f, -0.5f,}, {0, 0, 0},    {1, 1,}),
            Vertex({0.5f, 0.5f, -0.5f,}, {0, 0, 0},     {1, 0,}),

            Vertex({-0.5f, 0.5f, 0.5f,}, {0, 0, 0},     {0, 0,}),
            Vertex({-0.5f, -0.5f, 0.5f,}, {0, 0, 0},    {0, 1,}),
            Vertex({0.5f, -0.5f, 0.5f,}, {0, 0, 0},     {1, 1,}),
            Vertex({0.5f, 0.5f, 0.5f,}, {0, 0, 0},      {1, 0,}),

            Vertex({0.5f, 0.5f, -0.5f,}, {0, 0, 0},     {0, 0,}),
            Vertex({0.5f, -0.5f, -0.5f,}, {0, 0, 0},    {0, 1,}),
            Vertex({0.5f, -0.5f, 0.5f,}, {0, 0, 0},     {1, 1,}),
            Vertex({0.5f, 0.5f, 0.5f,}, {0, 0, 0},      {1, 0,}),

            Vertex({-0.5f, 0.5f, -0.5f,}, {0, 0, 0},    {0, 0,}),
            Vertex({-0.5f, -0.5f, -0.5f,}, {0, 0, 0},   {0, 1,}),
            Vertex({-0.5f, -0.5f, 0.5f,}, {0, 0, 0},    {1, 1,}),
            Vertex({-0.5f, 0.5f, 0.5f,}, {0, 0, 0},     {1, 0,}),

            Vertex({-0.5f, 0.5f, 0.5f,}, {0, 0, 0},     {0, 0,}),
            Vertex({-0.5f, 0.5f, -0.5f,}, {0, 0, 0},    {0, 1,}),
            Vertex({0.5f, 0.5f, -0.5f,}, {0, 0, 0},     {1, 1,}),
            Vertex({0.5f, 0.5f, 0.5f,}, {0, 0, 0},      {1, 0,}),

            Vertex({-0.5f, -0.5f, 0.5f,}, {0, 0, 0},    {0, 0,}),
            Vertex({-0.5f, -0.5f, -0.5f,}, {0, 0, 0},   {0, 1,}),
            Vertex({0.5f, -0.5f, -0.5f,}, {0, 0, 0},    {1, 1,}),
            Vertex({0.5f, -0.5f, 0.5f}, {0, 0, 0},      {1, 0}),
            }));


    HeapRef<std::vector<unsigned int>> indices(new std::vector<unsigned int>
        ({
            0, 1, 3,
            3, 1, 2,
            4, 5, 7,
            7, 5, 6,
            8, 9, 11,
            11, 9, 10,
            12, 13, 15,
            15, 13, 14,
            16, 17, 19,
            19, 17, 18,
            20, 21, 23,
            23, 21, 22
            }));
    
    Shader shader = Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
    Texture tex = Texture("res/textures/test2.png", true);

    HeapRef<Mesh> mesh = Mesh::Create(verts, indices);
    HeapRef<Material> mat = Material::Create(shader, tex);

    MeshRenderer rend = MeshRenderer(mesh, mat);

    GLFWwindow* window = Display::GetWindow();
    Graphics::Init(window);

    // Yucky yuck code just to get it working
    Camera cam;
    Transform trans;

    while (!glfwWindowShouldClose(window))
    {
        Time::Tick();

        cam.Update();

        //glm::vec3 t = glm::vec3(0, 0, -Time::deltaTime());
        //trans.Translate(t);

        Graphics::Clear();

        Graphics::YuckyYuckUploadMatrix(rend, cam, trans);

        //Graphics::Draw(rend);

        Graphics::PostRender();
    }

    return 0;
}