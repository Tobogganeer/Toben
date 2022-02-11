#pragma once

#include <string>
#include "../glm/vec2.hpp"
#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "../glm/mat4x4.hpp"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use();
    void Delete();
    //void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetU16Vec4(const std::string& name, const glm::u16vec4& value);
    void SetMat4(const std::string& name, const glm::mat4x4& value);
};