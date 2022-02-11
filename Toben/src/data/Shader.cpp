//https://learnopengl.com/Getting-started/Shaders
#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::ifstream vsStream(vertexPath);
    std::stringstream vs;
    vs << vsStream.rdbuf();

    std::ifstream fsStream(fragmentPath);
    std::stringstream fs;
    fs << fsStream.rdbuf();

    ID = CreateShader(vs.str(), fs.str());
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

Shader::~Shader()
{
    Delete();
}


void Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4x4& value) {
    
}


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Error handling
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        //char* message = (char*)alloca(length * sizeof(char));
        char message[512];
        glGetShaderInfoLog(shader, length, &length, message);
        const char* typeStr = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cout << "Failed to compile " << typeStr << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static unsigned int CreateShader(const std::string& vsSource, const std::string& fsSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vsSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}