//https://learnopengl.com/Getting-started/Shaders
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

#include "../core.h"
//#include "../vendor/glm/packing.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::ifstream vsStream(vertexPath);
    std::stringstream vs;
    vs << vsStream.rdbuf();

    std::ifstream fsStream(fragmentPath);
    std::stringstream fs;
    fs << fsStream.rdbuf();

    ID = Shader::CreateShader(vs.str(), fs.str());
}

void Shader::Bind()
{
    glUseProgram(ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

Shader::~Shader()
{
    Delete();
}

void Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetTexture(const std::string& name, int slot)
{
    SetInt(name, slot);
}

void Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4x4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

unsigned int Shader::CreateShader(const std::string& vsSource, const std::string& fsSource)
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

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniformCache.find(name) != uniformCache.end())
        return uniformCache[name];

    int loc = glGetUniformLocation(ID, name.c_str());

    if (loc == -1)
        std::cout << "[Shader Warning]: '" << name << "' doesnt exist!" << std::endl;
    uniformCache[name] = loc;

    return loc;
}