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
#include "utils/OBJLoader.h"

//https://github.com/g-truc/glm/blob/master/manual.md#section1
//https://github.com/g-truc/glm
//https://github.com/nothings/stb

#include <sstream>

int main(int argc, char* argv[])
{
    Display display;
    if (!display.Create(1280, 720, "Toben", false)) return -1;

    // Old, manual mesh input
    /*
    HeapRef<std::vector<Vertex>> verts(new std::vector<Vertex>
        ({
            Vertex({-0.5f, 0.5f, -0.5f,}, {0, 0, -1},    {0, 0,}),
            Vertex({-0.5f, -0.5f, -0.5f,}, {0, 0, -1},   {0, 1,}),
            Vertex({0.5f, -0.5f, -0.5f,}, {0, 0, -1},    {1, 1,}),
            Vertex({0.5f, 0.5f, -0.5f,}, {0, 0, -1},     {1, 0,}),

            Vertex({-0.5f, 0.5f, 0.5f,}, {0, 0, 1},     {0, 0,}),
            Vertex({-0.5f, -0.5f, 0.5f,}, {0, 0, 1},    {0, 1,}),
            Vertex({0.5f, -0.5f, 0.5f,}, {0, 0, 1},     {1, 1,}),
            Vertex({0.5f, 0.5f, 0.5f,}, {0, 0, 1},      {1, 0,}),

            Vertex({0.5f, 0.5f, -0.5f,}, {1, 0, 0},     {0, 0,}),
            Vertex({0.5f, -0.5f, -0.5f,}, {1, 0, 0},    {0, 1,}),
            Vertex({0.5f, -0.5f, 0.5f,}, {1, 0, 0},     {1, 1,}),
            Vertex({0.5f, 0.5f, 0.5f,}, {1, 0, 0},      {1, 0,}),

            Vertex({-0.5f, 0.5f, -0.5f,}, {-1, 0, 0},    {0, 0,}),
            Vertex({-0.5f, -0.5f, -0.5f,}, {-1, 0, 0},   {0, 1,}),
            Vertex({-0.5f, -0.5f, 0.5f,}, {-1, 0, 0},    {1, 1,}),
            Vertex({-0.5f, 0.5f, 0.5f,}, {-1, 0, 0},     {1, 0,}),

            Vertex({-0.5f, 0.5f, 0.5f,}, {0, 1, 0},     {0, 0,}),
            Vertex({-0.5f, 0.5f, -0.5f,}, {0, 1, 0},    {0, 1,}),
            Vertex({0.5f, 0.5f, -0.5f,}, {0, 1, 0},     {1, 1,}),
            Vertex({0.5f, 0.5f, 0.5f,}, {0, 1, 0},      {1, 0,}),

            Vertex({-0.5f, -0.5f, 0.5f,}, {0, -1, 0},    {0, 0,}),
            Vertex({-0.5f, -0.5f, -0.5f,}, {0, -1, 0},   {0, 1,}),
            Vertex({0.5f, -0.5f, -0.5f,}, {0, -1, 0},    {1, 1,}),
            Vertex({0.5f, -0.5f, 0.5f}, {0, -1, 0},      {1, 0}),
            }));


    HeapRef<std::vector<unsigned int>> indices(new std::vector<unsigned int>
        ({
            3, 1, 0, // back top right
            2, 1, 3, // back top left
            4, 5, 7, // front top left
            7, 5, 6, // front top right
            11, 9, 8, // right top right
            10, 9, 11, // right bottom left
            12, 13, 15, // left top left
            15, 13, 14, // left bottom right
            19, 17, 16, // top bottom left
            18, 17, 19, // top top right
            20, 21, 23, // bottom some face
            23, 21, 22 // bottom some face
            }));
    */

    Shader shader = Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");

    //std::cout << "args passed: " << argc << std::endl;

    if (argc < 2)
        std::cout << "Possible args: \n -model 'modelName.obj'\n -texture 'texName.ext'\n -scale #" << std::endl;

    std::string modelName = "Monkey.obj";
    std::string texName = "White.png";
    float scale = 1.0f;

    for (int i = 0; i < argc; i++)
    {
        //std::cout << "ARG: " << argv[i] << std::endl;

        std::string arg(argv[i]);
        if (arg.find("-model") != std::string::npos)
        {
            modelName = argv[i + 1];
            std::cout << "Set model to " << modelName << std::endl;
        }
        else if (arg.find("-texture") != std::string::npos)
        {
            texName = argv[i + 1];
            std::cout << "Set texture to " << texName << std::endl;
        }
        else if (arg.find("-scale") != std::string::npos)
        {
            scale = std::stof(argv[i + 1]);
            std::cout << "Set scale to " << scale << std::endl;
        }
        //std::cout << argv[i] << std::endl;
    }

    Texture tex = Texture("res/textures/" + texName, true);

    std::string model("res/models/" + modelName);
    HeapRef<Mesh> mesh = OBJLoader::Load(model, scale);

    //Texture tex = Texture("res/textures/shrek.jpg", true);
    //HeapRef<Mesh> mesh = OBJLoader::Load("res/models/Cube.obj");

    //Texture tex = Texture("res/textures/TR10 Texture.png", true);
    //HeapRef<Mesh> mesh = OBJLoader::Load("res/models/TR10.obj", 5.0f);

    //Texture tex = Texture("res/textures/White.png", true);
    //HeapRef<Mesh> mesh = OBJLoader::Load("res/models/Monkey.obj");

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

        Graphics::Clear();

        // cam = vec3(4, 2, 2)
        glm::vec3 lightPos = glm::vec3(4, 2, 2);
        glm::vec3 lightDir = glm::normalize(lightPos);

        Graphics::YuckyYuckUploadMatrix(rend, cam, trans, lightDir);

        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = glm::vec3(1, 0, 0);
        trans.Rotate(Time::deltaTime() * 180, up);
        //cam.Translate(up);
        //cam.Rotate(Time::deltaTime() * 10, right);
        //cam.Rotate(Time::deltaTime() * 3, up);
        //cam.Rotate(Time::deltaTime() * 15 * glm::sin(Time::time() * 3), up);

        //Graphics::Draw(rend);

        Graphics::PostRender();
    }

    return 0;
}