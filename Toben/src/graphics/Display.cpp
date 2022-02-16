#include "Display.h"
#include <iostream>

GLFWwindow* Display::window;
int Display::width;
int Display::height;
Display Display::instance;

GLFWwindow* Display::GetWindow()
{
	return window;
}

bool Display::Create(int width, int height, const char* title, bool vsync)
{
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FOCUSED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);

    glfwSetErrorCallback(glErrorCallback);

    Display::width = width;
    Display::height = height;
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error Initializing GLEW!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, width, height);
    glfwSwapInterval(vsync);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Display::Resize(int width, int height)
{
    Display::width = width;
    Display::height = height;

    glViewport(0, 0, width, height);
}

void Display::glErrorCallback(int error, const char* description)
{
	fprintf(stderr, "[OpenGL Error]: %s\n", description);
}

Display::Display()
{

}

Display::~Display()
{
    glfwTerminate();
}