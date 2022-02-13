#pragma once

#include <string>
//#include "../vendor/glm/vec2.hpp"
//#include "../vendor/glm/vec3.hpp"
//#include "../vendor/glm/vec4.hpp"
#include "../vendor/glm/mat4x4.hpp"
#include <unordered_map>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Bind();
    void Unbind();
    void Delete();
    //void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetTexture(const std::string& name, int slot);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, float x, float y);
    void SetVec3(const std::string& name, float x, float y, float z);
    void SetVec4(const std::string& name, float x, float y, float z, float w);
    void SetMat4(const std::string& name, const glm::mat4x4& value);

    int GetUniformLocation(const std::string& name);

private:
    unsigned int ID;

    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static unsigned int CreateShader(const std::string& vsSource, const std::string& fsSource);
    std::unordered_map<std::string, int> uniformCache;
};